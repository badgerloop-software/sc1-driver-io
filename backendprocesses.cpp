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



//BackendProcesses::BackendProcesses(QObject *parent) : QObject(parent)
BackendProcesses::BackendProcesses(QByteArray &bytes, std::vector<float> &floatData, std::vector<char> &charData, std::vector<uint8_t> &boolData, std::vector<uint8_t> &uint8_tData, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent) : QObject(parent), bytes(bytes), floatData(floatData), charData(charData), boolData(boolData), uint8_tData(uint8_tData), names(names), types(types)
{
    this->bytes = bytes;
    this->floatData = floatData;
    this->uint8_tData = uint8_tData;
    this->charData = charData;
    this->boolData = boolData;
    this->names = names;
    this->types = types;

    time = 0; // TODO it would probably be best to include timestamps in the TCP payloads in case of delay in packets arriving (wouldn't need to add them to the format)

    /*DataUnpacker* unpacker = new DataUnpacker(floatData, charData, boolData, uint8_tData, names, types);

    unpacker->moveToThread(&dataHandlingThread);
    connect(&dataHandlingThread, &QThread::started, unpacker, &DataUnpacker::startThread);
    connect(this, &BackendProcesses::getData, unpacker, &DataUnpacker::threadProcedure);
    connect(unpacker, &DataUnpacker::dataReady, this, &BackendProcesses::handleData);
    connect(&dataHandlingThread, &QThread::finished, unpacker, &QObject::deleteLater);
    connect(&dataHandlingThread, &QThread::finished, &dataHandlingThread, &QThread::deleteLater);

    dataHandlingThread.start();*/
}

/*BackendProcesses::~BackendProcesses()
{
    dataHandlingThread.quit();
}*/

/*void BackendProcesses::handleData()
{
    // Update data fields

    int numFloats = 0;
    int numUint8_ts = 0;
    int numChars = 0;
    int numBools = 0;

    for(uint i=0; i < names.size(); i++) {
        // Check the type and set the appropriate property
        if(types[i] == "float") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), floatData[numFloats]);
            }
            numFloats++;
        } else if(types[i] == "uint8") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), uint8_tData[numUint8_ts]);
            }
            numUint8_ts++;
        } else if(types[i] == "bool") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), (bool) boolData[numBools]);
            }
            numBools++;
        } else if(types[i] == "char") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                // NOTE: char data is displayed as its ASCII decimal value, not the character, so QString is used instead
                this->setProperty(names[i].c_str(), QString::fromStdString(std::string(1, charData[numChars])));
            }
            numChars++;
        } else if(types[i] == "double") {
            // TODO: No double data yet; Implement when there is double data
        }
    }

    // Signal data update for front end
    emit dataChanged();
    // Signal to get new data
    emit getData();
}*/

void BackendProcesses::onNewConnection()
{
   QTcpSocket *clientSocket = _server.nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
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
    }
}

void BackendProcesses::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    for (QTcpSocket* socket : _sockets) {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
    }
}

void BackendProcesses::startThread()
{
    _server.listen(QHostAddress::AnyIPv4, 4003);
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    threadProcedure();
}

void BackendProcesses::threadProcedure()
{
    DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);

    bytes.clear();

    data.getData(bytes, names, types, time);

    for (QTcpSocket* socket : _sockets) {
        //socket->write(QByteArray::fromStdString("From solar car: connected to server! " + std::to_string(time) + "\n"));
        //socket->write(QByteArray::fromStdString("Speed: " + std::to_string(speed) + "; Size: " + std::to_string(sizeof(bytes)) + "\n"));
        socket->write(bytes);
    }

    time = (time < 7) ? (time + 0.25) : 0;

    usleep(1000000 );
    emit dataReady();
}
