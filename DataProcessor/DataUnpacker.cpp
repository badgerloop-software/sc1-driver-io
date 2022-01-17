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



//DataUnpacker::DataUnpacker(unpackedData &processedData, QObject *parent) : QObject(parent), processedData(processedData)
DataUnpacker::DataUnpacker(unpackedData &processedData, std::vector<float> &floatData, std::vector<char> &charData, std::vector<bool> &boolData, std::vector<uint8_t> &uint8_tData, QObject *parent) : QObject(parent), floatData(floatData), charData(charData), boolData(boolData), uint8_tData(uint8_tData), processedData(processedData)// TODO , processedData(processedData)
{
    this->processedData = processedData; // TODO

    QString fileContents;
    QFile file;
    file.setFileName("../sc1-data-format/format.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContents = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(fileContents.toUtf8());
    format = d.object();
    // Initialize
    // TODO names = format.keys(); // TODO It's sorted lexographically
    QJsonObject::const_iterator currElement = format.begin(); // TODO It's still sorted, and there's no way around it. Look into another JSON parsing library
    QJsonObject::const_iterator end = format.end();
    /* TODO for(const QString& i : names) {
        QJsonArray currValue = format[i].toArray();
        byteNums.push_back(currValue[0].toInt());
        types.push_back(currValue[1].toString());
    }*/
    int eCount = 0;
    while((currElement != end)) {// || (eCount >= 3)) {
        QJsonArray currValue = currElement.value().toArray();
        names.push_back(currElement.key());
        byteNums.push_back(currValue[0].toInt());
        types.push_back(currValue[1].toString());
        currElement++;
        eCount ++;
    }
    //QJsonArray value = format["solarPower"].toArray();
    //QJsonArray value = format.value(QString("speed")).toArray();
    //QJsonObject item = value.toObject();
    //QJsonArray test = value["imp"].toArray();
    //speedTest = value[0].toInt();
    speedTest = types[20].at(0).unicode(); // TODO It's still sorted, and there's no way around it. Look into another JSON parsing library
    //speedTest = byteNums[2]; // TODO

    time = 0;

    /* TODO
    std::vector<std::string> names;
    std::vector<uint8_t> sizes;
    std::vector<std::string> types;*/
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
    // TODO Definitely handle this using a for loop and the arrays created in constructor using format.jsom

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

    // TODO Could try setting up Q_PROPERTYs for each data field and loop through and set them using setProperty() w/ the names & data in the arrays created in the constructor
    // Update unpackedData struct for BackendProcesses
    // TODO Remove individual data members from DataUnpacker and use these in unpack (need to change bytesToDouble() to bytesToFloat())
    //processedData.speed = speed;
    processedData.speed = speedTest;
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


