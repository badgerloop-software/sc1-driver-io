//
// Created by Mingcan Li on 11/16/21.
//

#include "DataUnpacker.h"

double speedFunc(double t){
    return t*t;
}

double solarFunc(double t){
    return t*t*t;
}

double batteryFunc(double t){
    return pow(2.71828,-t)*100;
}

double bytesToDouble(std::vector<byte> data, int start_pos) {
    double number;
    memcpy(&number, &data.at(start_pos), sizeof(double));
    return number;
}

template <typename E>
void bytesToSomethingNotDouble(std::vector<byte> data, int startPos, int endPos, E &var){
    int byteNum=endPos-startPos;
    for(int i = startPos ; i<=endPos ; i++) {
        var=var+data[i]<<byteNum*8;
        byteNum--;
    }
}



//int 4 bytes double 8 bytes char 1 bytes
DataUnpacker::DataUnpacker(unpackedData &processedData, QObject *parent) : QObject(parent), processedData(processedData)
{
    // TODO
    this->processedData = processedData;
    time = 0;
    //processedData2 = (*unpackedData)calloc(1, sizeof(unpackedData));
    std::vector<unsigned char> bytes;
    DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);
    data.getData(bytes,3);
    //bytes.clear();
    //data.getData(bytes,2);
    unpack(bytes);

    // TODO _server.listen(QHostAddress::AnyIPv4, 4003);
    // TODO connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    //ui->setupUi(this);
    //startThread(); // TODO
    //state = 'D'; // TODO
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
    for (QTcpSocket* socket : _sockets) {
        socket->write(QByteArray::fromStdString("From solar car: " + clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }
}

void DataUnpacker::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        //_sockets.removeOne(sender);
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

void DataUnpacker::unpack(std::vector<byte> rawData) {
    bytesToSomethingNotDouble(rawData, 0, 3, speed);
    power=bytesToDouble(rawData,4);
    bytesToSomethingNotDouble(rawData, 12, 15, charge);
    solarP=bytesToDouble(rawData,16);
    netP= bytesToDouble(rawData,24);
    motorP= bytesToDouble(rawData,32);
    bytesToSomethingNotDouble(rawData,40,40,state);
    batteryT= bytesToDouble(rawData,41);
    motorT= bytesToDouble(rawData,49);
    motorControllerT= bytesToDouble(rawData,57);
    bytesToSomethingNotDouble(rawData,65,65,bpsFault);
    bytesToSomethingNotDouble(rawData,66,66,eStop);
    bytesToSomethingNotDouble(rawData,67,67,cruise);
    bytesToSomethingNotDouble(rawData,68,68,lt);
    bytesToSomethingNotDouble(rawData,69,69,rt);
    bytesToSomethingNotDouble(rawData,70,73,flTp);
    bytesToSomethingNotDouble(rawData,74,77,frTp);
    bytesToSomethingNotDouble(rawData,78,81,rlTp);
    bytesToSomethingNotDouble(rawData,82,85,rrTp);
}


void DataUnpacker::startThread() {
    // TODO t = std::thread(&DataUnpacker::threadProcedure,this);
    // TODO t.detach();

    _server.listen(QHostAddress::AnyIPv4, 4003);
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    threadProcedure();
    //t = QThread::create(&DataUnpacker::threadProcedure,this);
    //_server.moveToThread(&t);
    // TODO connect(&t, &QThread::started, this, &DataUnpacker::threadProcedure);
    // TODO t.start();
}

void DataUnpacker::threadProcedure() {
    DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);

    // TODO for( ; ; ) {
        std::vector<unsigned char> bytes;
        data.getData(bytes,time);

        for (QTcpSocket* socket : _sockets) {
            //socket->write(QByteArray::fromStdString("From solar car: connected to server! " + std::to_string(time) + "\n"));
            socket->write(QByteArray::fromStdString("From solar car: connected to server! " + std::to_string(time) + "\n"));
        }

        unpack(bytes);

        // Update unpackedData struct for BackendProcesses
        // TODO Remove individual data members from DataUnpacker and use these in unpack (need to change bytesToDouble() to bytesToFloat())
        processedData.speed = speed;
        processedData.charge = charge;
        processedData.flTp = flTp;
        processedData.frTp = frTp;
        processedData.rlTp = rlTp;
        processedData.rrTp = rrTp;
        processedData.solarPower = (float) solarP;
        processedData.motorPower = (float) motorP;
        processedData.netPower = (float) netP;
        processedData.batteryTemp = (float) batteryT;
        processedData.motorTemp = (float) motorT;
        processedData.motorControllerTemp = (float) motorControllerT;
        processedData.bpsFault = bpsFault;
        processedData.eStop = eStop;
        processedData.cruiseControl = cruise;
        processedData.leftTurn = lt;
        processedData.rightTurn = rt;
        processedData.state = state;

        time = (time + 1) % 9;
        usleep(1000000 );
        emit dataReady();
    // TODO }
}


