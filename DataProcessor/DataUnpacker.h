//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAPROCESSOR_DATAUNPACKER_H
#define DATAPROCESSOR_DATAUNPACKER_H

#include <vector>
#include <unistd.h>
#include <QObject>
// TODO #include <QFile>
/* TODO
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>*/
#include <QTcpServer>
#include <QTcpSocket>
#include "DataGen.h"
#include "UnpackedData.h"
#include "3rdparty/rapidjson/document.h"
#include "3rdparty/rapidjson/filereadstream.h"
//#include <cstdio> //TODO


using namespace rapidjson;

typedef unsigned char byte;

class DataUnpacker : public QObject
{
    Q_OBJECT

public:
    // TODO explicit DataUnpacker(unpackedData &processedData, QObject *parent = nullptr);
    // TODO Watch vector type for boolData
    explicit DataUnpacker(unpackedData &processedData, std::vector<float> &floatData, std::vector<char> &charData, std::vector<uint8_t> &boolData, std::vector<uint8_t> &uint8_tData, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent = nullptr); // TODO Remove processedData
    //~DataUnpacker(); // TODO
    void unpack(QByteArray rawData);
public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

    void threadProcedure();
    void startThread();
signals:
    void dataReady();
private:
    unpackedData& processedData; // TODO
    double time;
    uint8_t speed, charge, flTp, frTp, rlTp, rrTp;
    float batteryV, batteryI, solarP, netP, motorP, batteryT, motorT, motorControllerT, batteryGroup1, batteryGroup2, batteryGroup3, batteryGroup4;
    bool bpsFault, eStop, cruise, lt, rt;
    char state;
    // TODO
    std::vector<float> &floatData;
    std::vector<char> &charData;
    std::vector<uint8_t> &boolData; // TODO It didn't like passing a bool to bytesToSomethingNotDouble for some reason
    std::vector<uint8_t> &uint8_tData;
    // TODO QStringList names;
    std::vector<std::string> &names;
    std::vector<int> byteNums;
    std::vector<std::string> &types;
    // TODO QStringList types;
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;
    //QJsonObject format; // TODO

    int speedTest; // TODO
};


#endif //DATAGENERATOR_DATAUNPACKER_H
