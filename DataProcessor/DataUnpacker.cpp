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



DataUnpacker::DataUnpacker(std::vector<float> &floatData, std::vector<char> &charData, std::vector<uint8_t> &boolData, std::vector<uint8_t> &uint8_tData, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent) : QObject(parent), floatData(floatData), charData(charData), boolData(boolData), uint8_tData(uint8_tData), names(names), types(types)
{
    this->floatData = floatData;
    this->uint8_tData = uint8_tData;
    this->charData = charData;
    this->boolData = boolData;
    this->names = names;
    this->types = types;

    // pi needs an absolute filepath
    FILE* fp = fopen("/absolute/file/path/here/solar-car-dashboard/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    if(fp == 0) {
        // testing
        fp = fopen("../sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    }

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    for(Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
        std::string name = itr->name.GetString();
        const Value& arr = itr->value.GetArray();
        names.push_back(name);
        byteNums.push_back(arr[0].GetInt());
        types.push_back(arr[1].GetString());
    }

    fclose(fp);

    time = 0; // TODO it would probably be best to include timestamps in the TCP payloads in case of delay in packets arriving (wouldn't need to add them to the format)
}

/*DataUnpacker::~DataUnpacker(){}*/

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
    int currByte = 0;
    uint numFloats = 0;
    uint numUint8_ts = 0;
    uint numChars = 0;
    uint numBools = 0;

    for(uint i=0; i < names.size(); i++) {
        if(types[i] == "float") {
            if(floatData.size() == numFloats) {
                floatData.push_back(0.0f);
            }
            floatData[numFloats] = bytesToFloat(rawData, currByte);
            numFloats++;
        } else if(types[i] == "uint8") {
            if(uint8_tData.size() == numUint8_ts) {
                uint8_tData.push_back(0);
            }
            bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, uint8_tData[numUint8_ts]);
            numUint8_ts++;
        } else if(types[i] == "bool") {
            if(boolData.size() == numBools) {
                boolData.push_back(false);
            }
            bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, boolData[numBools]);
            numBools++;
        } else if(types[i] == "char") {
            if(charData.size() == numChars) {
                charData.push_back('0');
            }
            bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, charData[numChars]);
            numChars++;
        } else if(types[i] == "double") {
            // TODO: No double data yet; Implement when there is double data
        }
        currByte += byteNums[i];
    }
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

    data.getData(bytes, names, types, time);

    unpack(bytes);

    for (QTcpSocket* socket : _sockets) {
        //socket->write(QByteArray::fromStdString("From solar car: connected to server! " + std::to_string(time) + "\n"));
        //socket->write(QByteArray::fromStdString("Speed: " + std::to_string(speed) + "; Size: " + std::to_string(sizeof(bytes)) + "\n"));
        socket->write(bytes);
    }

    time = (time < 7) ? (time + 0.25) : 0;

    usleep(1000000 );
    emit dataReady();
}


