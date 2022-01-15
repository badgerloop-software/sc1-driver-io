//
// Created by Mingcan Li on 11/16/21.
//

#include "DataUnpacker.h"

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

double bytesToDouble(QByteArray data, int start_pos)
{
    double number;
    char* dataPtr = data.data();
    memcpy(&number, &dataPtr[start_pos], sizeof(double));
    return number;
}

float bytesToFloat(QByteArray data, int start_pos)
{
    float number;
    char* dataPtr = data.data();
    memcpy(&number, &dataPtr[start_pos], sizeof(float));
    return number;
}

template <typename E>
void bytesToSomethingNotDouble(QByteArray data, int startPos, int endPos, E &var)
{
    int byteNum=endPos-startPos;
    var = 0;
    for(int i = startPos ; i<=endPos ; i++) {
        var=var+data[i]<<byteNum*8;
        byteNum--;
    }
}



DataUnpacker::DataUnpacker(unpackedData &processedData, QObject *parent) : QObject(parent), processedData(processedData)
{
    this->processedData = processedData;
    time = 0;
}

/*DataUnpacker::~DataUnpacker()
{
    //t.quit();
}*/

void DataUnpacker::onNewConnection()
{
   QTcpSocket *clientSocket = _server.nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
    /*for (QTcpSocket* socket : _sockets) {
        socket->write(QByteArray::fromStdString("From solar car: " + clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }*/
}

void DataUnpacker::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}

void DataUnpacker::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    for (QTcpSocket* socket : _sockets) {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
    }
}

void DataUnpacker::unpack(QByteArray rawData)
{
    bytesToSomethingNotDouble(rawData, 0, 0, speed);
    bytesToSomethingNotDouble(rawData, 1, 1, charge);
    solarP = bytesToFloat(rawData,2);
    batteryV = bytesToFloat(rawData,6);
    batteryI = bytesToFloat(rawData,10);
    netP = bytesToFloat(rawData,14);
    motorP = bytesToFloat(rawData,18);
    bytesToSomethingNotDouble(rawData,22,22,state);
    batteryT = bytesToFloat(rawData,23);
    motorT = bytesToFloat(rawData,27);
    motorControllerT = bytesToFloat(rawData,31);
    bytesToSomethingNotDouble(rawData,35,35,bpsFault);
    bytesToSomethingNotDouble(rawData,36,36,eStop);
    bytesToSomethingNotDouble(rawData,37,37,cruise);
    bytesToSomethingNotDouble(rawData,38,38,lt);
    bytesToSomethingNotDouble(rawData,39,39,rt);
    bytesToSomethingNotDouble(rawData,40,40,flTp);
    bytesToSomethingNotDouble(rawData,41,41,frTp);
    bytesToSomethingNotDouble(rawData,42,42,rlTp);
    bytesToSomethingNotDouble(rawData,43,43,rrTp);
    batteryGroup1 = bytesToFloat(rawData,44);
    batteryGroup2 = bytesToFloat(rawData,48);
    batteryGroup3 = bytesToFloat(rawData,52);
    batteryGroup4 = bytesToFloat(rawData,56);
}


void DataUnpacker::startThread()
{
    _server.listen(QHostAddress::AnyIPv4, 4003);
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    threadProcedure();
}

void DataUnpacker::threadProcedure()
{
    DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);

    QByteArray bytes;
    data.getData(bytes,time);

    unpack(bytes);

    // Update unpackedData struct for BackendProcesses
    // TODO Remove individual data members from DataUnpacker and use these in unpack (need to change bytesToDouble() to bytesToFloat())
    processedData.speed = speed;
    processedData.charge = charge;
    processedData.solarPower = solarP;
    processedData.batteryVoltage = batteryV;
    processedData.batteryCurrent = batteryI;
    processedData.netPower = netP;
    processedData.motorPower = motorP;
    processedData.state = state;
    processedData.batteryTemp = batteryT;
    processedData.motorTemp = motorT;
    processedData.motorControllerTemp = motorControllerT;
    processedData.bpsFault = bpsFault;
    processedData.eStop = eStop;
    processedData.cruiseControl = cruise;
    processedData.leftTurn = lt;
    processedData.rightTurn = rt;
    processedData.flTp = flTp;
    processedData.frTp = frTp;
    processedData.rlTp = rlTp;
    processedData.rrTp = rrTp;
    processedData.bat1 = batteryGroup1;
    processedData.bat2 = batteryGroup2;
    processedData.bat3 = batteryGroup3;
    processedData.bat4 = batteryGroup4;

    for (QTcpSocket* socket : _sockets) {
        //socket->write(QByteArray::fromStdString("From solar car: connected to server! " + std::to_string(time) + "\n"));
        //socket->write(QByteArray::fromStdString("Speed: " + std::to_string(speed) + "; Size: " + std::to_string(sizeof(bytes)) + "\n"));
        socket->write(bytes);
    }

    time = (time + 1) % 9;
    usleep(1000000 );
    emit dataReady();
}


