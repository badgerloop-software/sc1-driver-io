//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAPROCESSOR_DATAUNPACKER_H
#define DATAPROCESSOR_DATAUNPACKER_H

#include <vector>
#include <unistd.h>
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QTcpServer>
#include <QTcpSocket>
#include "DataGen.h"
#include "UnpackedData.h"

typedef unsigned char byte;

class DataUnpacker : public QObject
{
    Q_OBJECT

public:
    // TODO explicit DataUnpacker(unpackedData &processedData, QObject *parent = nullptr);
    explicit DataUnpacker(unpackedData &processedData, std::vector<float> &floatData, std::vector<char> &charData, std::vector<bool> &boolData, std::vector<uint8_t> &uint8_tData, QObject *parent = nullptr);
    //~DataUnpacker(); TODO
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
    int time;
    uint8_t speed, charge, flTp, frTp, rlTp, rrTp;
    float batteryV, batteryI, solarP, netP, motorP, batteryT, motorT, motorControllerT, batteryGroup1, batteryGroup2, batteryGroup3, batteryGroup4;
    bool bpsFault, eStop, cruise, lt, rt;
    char state;
    // TODO
    std::vector<float> &floatData;
    std::vector<char> &charData;
    std::vector<bool> &boolData;
    std::vector<uint8_t> &uint8_tData;
    QStringList names;
    std::vector<int> byteNums;
    // TODO std::vector<std::string> types;
    QStringList types;
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;
    QJsonObject format;
    int speedTest;
};


#endif //DATAGENERATOR_DATAUNPACKER_H
