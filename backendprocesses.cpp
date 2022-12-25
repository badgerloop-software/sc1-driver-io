#include "backendprocesses.h"

double speedFunc(double t)
{
    return t*t;
}

double solarFunc(double t)
{
    return t*t*t;
}

double batteryFunc(double t)
{
    return pow(2.71828,-t)*100;
}



BackendProcesses::BackendProcesses(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, timestampOffsets timeDataOffsets, QMutex &mutex, QObject *parent) : QObject(parent), bytes(bytes), names(names), types(types), mutex(mutex)
{
    //this->bytes = bytes;
    //this->names = names;
    //this->types = types;
    this->tstampOffsets.hr = timeDataOffsets.hr;
    this->tstampOffsets.mn = timeDataOffsets.mn;
    this->tstampOffsets.sc = timeDataOffsets.sc;
    this->tstampOffsets.ms = timeDataOffsets.ms;
}

/*BackendProcesses::~BackendProcesses(){}*/

void BackendProcesses::onNewConnection()
{
   QTcpSocket *clientSocket = _server.nextPendingConnection();
   //connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
    emit eng_dash_connection(1);
    /*for (QTcpSocket* socket : _sockets) {
        socket->write(QByteArray::fromStdString("From solar car: " + clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }*/
}

void BackendProcesses::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
        emit eng_dash_connection(0);
    }
}

/*void BackendProcesses::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    for (QTcpSocket* socket : _sockets) {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
    }
}*/

void BackendProcesses::startThread()
{
    _server.listen(QHostAddress::AnyIPv4, 4003);
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    // TODO For the database testing: Record the start time of the thread
    first_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    // TODO Create a QNetworkAccessManager for sending HTTP requests to the VPS
    this->restclient = new QNetworkAccessManager();
    // TODO Automatically delete server response since it isn't used
    this->restclient->setAutoDeleteReplies(true);

    threadProcedure();
}

void BackendProcesses::threadProcedure()
{
    usleep(50000);

    DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);

    mutex.lock();

    bytes.clear();

    // Get time data is received (then written to byte array right after byte array is updated/data is received)
    auto curr_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    qDebug() << curr_msec;
    //time_t now = time(NULL);

    uint8_t hour_time = (curr_msec/3600000 + 18) % 24;
    //uint8_t hour_time = (gmtime(&now)->tm_hour + 18) % 24;
    uint8_t min_time = (curr_msec/60000) % 60;
    //uint8_t min_time = gmtime(&now)->tm_min;
    uint8_t sec_time = (curr_msec/1000) % 60;
    //uint8_t sec_time = gmtime(&now)->tm_sec;
    uint16_t msec_time = curr_msec % 1000;

    data.getData(bytes, names, types, sec_time%7+msec_time/1000.0);

    // Update timestamp in byte array
    bytes.remove(tstampOffsets.hr,1);
    bytes.insert(tstampOffsets.hr, hour_time & 0xFF);
    bytes.remove(tstampOffsets.mn,1);
    bytes.insert(tstampOffsets.mn, min_time & 0xFF);
    bytes.remove(tstampOffsets.sc,1);
    bytes.insert(tstampOffsets.sc, sec_time & 0xFF);
    bytes.remove(tstampOffsets.ms,2);
    bytes.insert(tstampOffsets.ms, msec_time & 0xFF);
    bytes.insert(tstampOffsets.ms, (msec_time >> 8) & 0xFF);

    // Create URL for HTTP request to send byte array to the server
    QUrl myurl;
    myurl.setScheme("http");
    myurl.setHost("hostname"); // TODO Put this (and other database info) in constants file that is ignored by Git
    myurl.setPort(9999);
    myurl.setPath("/add-data");

    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer")); // TODO Try "blob" for content type as well

    // TODO SPLIT THIS UP INTO TWO PARTS:
    //          1. session-time: (first_msec) start time of the session (used to identify which table the data should be inserted into)
    //          2. dataset-time: (curr_msec) timestamp associated with the byte array being sent to the server
    request.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("identifier; session-time=" + QString::fromStdString(std::to_string(curr_msec))));



    // TODO This breaks after a bit, so don't keep creating new objects. Be smart about memory
    //QNetworkAccessManager restclient(this);
    // TODO QNetworkAccessManager *restclient; //in class
    //QScopedPointer<QNetworkAccessManager> restclient(new QNetworkAccessManager()); //constructor
    // TODO restclient = new QNetworkAccessManager();

    // TODO file->setParent(restclient); // Cannot delete the file now, so delete it with the restclient

    // TODO connect(restclient, &QNetworkAccessManager::finished,
    //        restclient, &QNetworkAccessManager::deleteLater);
    //connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
    //connect(restclient, &QNetworkAccessManager::finished,
    //        restclient, &QNetworkAccessManager::deleteLater);

    //QNetworkAccessManager restclient;
    //reply = restclient.post(request, bytes);




    // TODO A bit complicated of a method:
    //      Connect the reply or QNetworkAccessmanager finished() method to the QNetworkAccessManager deleteLater() method
    //      Then, accumulate bytes and timestamps to an array that is sent en masse to the server after the current restclient is finished, deleted, and recreated

    //TODO this->restclient->moveToThread(this->thread());

    qDebug() << this->thread() << "\t\t" << restclient->thread() << "\t\t" << sec_counter;

    // TODO Allows HTTP pipelining so that the request doesn't wait for a response from the server before allowing a new message to be sent
    //      This should help to avoid stalling while waiting for a response from the server
    request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);

    // TODO Post the byte array, along with the corresponding timestamp, to the server
    reply = this->restclient->post(request, bytes);

    //qDebug() << "\n------------------------------------------------------------------\nSENT POST REQUEST";
    //qDebug() << request.attribute(QNetworkRequest::HttpPipeliningAllowedAttribute);
    //qDebug() << request.attribute(QNetworkRequest::HttpPipeliningWasUsedAttribute);
    //qDebug() << "------------------------------------------------------------------\n";

    //connect(reply, &QNetworkReply::finished, reply, &QNetworkReply::deleteLater);
    //connect(reply, &QNetworkReply::finished, restclient, &QNetworkAccessManager::deleteLater);

    //connect(restclient, &QNetworkAccessManager::finished,
    //        reply, &QNetworkReply::deleteLater);


    //restclient->deleteLater(); // TODO



    /* TODO
    // Call readReply() whenever the reply is ready to be read (on readyRead emitted)
    // TODO connect(this->reply, &QNetworkReply::readyRead, this, &BackendProcesses::readReply);

    // TODO usleep(245000); // Wait for readyRead to be emitted

    // Guessing waitForReadyRead() doesn't work because this is in a different thread than the one backendProcesses was initialized in
    //reply->waitForReadyRead(-1);

    //qDebug() << reply->readAll();



    /*QVariantMap feed;
    feed.insert("t1","10101");
    feed.insert("t2",QString::fromStdString(std::to_string(wazzup_counter++)));

    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();



    qDebug() << "PAYLOAD: " << QVariant(payload).toString();

    QUrl myurl2;
    myurl2.setScheme("https");
    myurl2.setHost("test-project-jrv-default-rtdb.firebaseio.com");
    myurl2.setPath("/bytes/session" + QString::fromStdString(std::to_string(wazzup_counter++)) + ".json");

    QNetworkRequest request2;
    request2.setUrl(myurl2);
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    qDebug() << "URL: " << myurl2.toString();

    QNetworkAccessManager *restclient2; //in class
    restclient2 = new QNetworkAccessManager(this); //constructor
    QNetworkReply *reply2 = restclient2->post(request2,payload);
    qDebug() << reply2->readAll();*/


    /*
    QVariantMap feed;
    feed.insert("session","sess5");
    feed.insert("tstamp","t");
    feed.insert("bytes","010101");
    feed.insert("counter",wazzup_counter++);

    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();



    qDebug() << "PAYLOAD: " << QVariant(payload).toString();

    QUrl myurl2;
    myurl2.setScheme("https");
    myurl2.setHost("$ASTRA_DB_ID-$ASTRA_DB_REGION.apps.astra.datastax.com");
    myurl2.setPath("/api/rest/v2/keyspaces/blooptests/table1");

    QNetworkRequest request2;
    request2.setUrl(myurl2);
    request2.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request2.setRawHeader("x-cassandra-token", "$ASTRA_DB_APPLICATION_TOKEN"); // TODO May have to cast these to byte arrays
    //Not a known header: request2.setHeader("x-cassandra-token", "$ASTRA_DB_APPLICATION_TOKEN");

    qDebug() << "URL: " << myurl2.toString();

    QNetworkAccessManager *restclient2; //in class
    restclient2 = new QNetworkAccessManager(this); //constructor
    QNetworkReply *reply2 = restclient2->post(request2,payload);
    qDebug() << reply2->readAll();*/

    wazzup_counter ++;

    // TODO Display the number of entries inserted each second
    if(((curr_msec - first_msec) / 1000) > sec_counter) {
        qDebug() << "Wazzups/sec: " << (wazzup_counter - prev_wazzup_counter);
        qDebug() << "Wazzups: " << wazzup_counter;

        prev_wazzup_counter = wazzup_counter;
        sec_counter ++;
    }


    for (QTcpSocket* socket : _sockets) {
        //socket->write(QByteArray::fromStdString("From solar car: connected to server! " + std::to_string(time) + "\n"));
        //socket->write(QByteArray::fromStdString("Speed: " + std::to_string(speed) + "; Size: " + std::to_string(sizeof(bytes)) + "\n"));
        socket->write(bytes);
    }
    mutex.unlock();
    emit dataReady();
}

// TODO Read reply from server
void BackendProcesses::readReply() {
    qDebug() << "HTTP response: " << reply->readAll();

}
