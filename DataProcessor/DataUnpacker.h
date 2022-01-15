//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAPROCESSOR_DATAUNPACKER_H
#define DATAPROCESSOR_DATAUNPACKER_H

#include <vector>
#include <QObject>
#include "DataGen.h"
#include "UnpackedData.h"
#include <unistd.h>
#include <QTcpServer>
#include <QTcpSocket>

typedef unsigned char byte;

class DataUnpacker : public QObject
{
    Q_OBJECT

public:
    explicit DataUnpacker(unpackedData &processedData, QObject *parent = nullptr);
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
    unpackedData& processedData;
    int time;
    uint8_t speed, charge, flTp, frTp, rlTp, rrTp;
    float batteryV, batteryI, solarP, netP, motorP, batteryT, motorT, motorControllerT, batteryGroup1, batteryGroup2, batteryGroup3, batteryGroup4;
    bool bpsFault, eStop, cruise, lt, rt;
    char state;
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;
};


#endif //DATAGENERATOR_DATAUNPACKER_H
