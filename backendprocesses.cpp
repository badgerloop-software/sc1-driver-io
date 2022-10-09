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


    // TODO for database testing
    restclient = new QNetworkAccessManager(); //constructor

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


    //QUrlQuery querystr;
    //querystr.addQueryItem("field1","Wazzup");
    //querystr.addQueryItem("field2",QString::fromStdString(std::to_string(wazzup_counter++)));

    /*QUrl myurl;
    myurl.setScheme("http");
    myurl.setHost("recipes-instance");
    myurl.setPort(5000);
    myurl.setUserName("ubuntu");
    myurl.setPath("/apis");
    //myurl.setQuery(querystr);

    QNetworkRequest request;
    request.setUrl(myurl);
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager *restclient; //in class
    restclient = new QNetworkAccessManager(); //constructor
    QNetworkReply *reply = restclient->get(request);*/

    // TODO Insert data via a REST API call
    querystr.addQueryItem("field1","Wazzup");
    querystr.addQueryItem("field2",QString::fromStdString(std::to_string(wazzup_counter++)));


    myurl.setScheme("https");
    myurl.setHost("g5079b74c17c11c-allrecipes.adb.us-ashburn-1.oraclecloudapps.com");
    myurl.setPath("/ords/admin/test-select/api/add-row-1");
    myurl.setQuery(querystr);

    request.setUrl(myurl);
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");



    reply = restclient->get(request);
    //qDebug() << reply->readAll();

    querystr.clear();




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

    // Display the number of entries inserted each second
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
