//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAPROCESSOR_DATAUNPACKER_H
#define DATAPROCESSOR_DATAUNPACKER_H

#include <QObject>
#include <QThread>
//#include <QTcpServer>
//#include <QTcpSocket>
//#include <vector>
//#include <unistd.h>
#include "DataGen.h"
#include "backendprocesses.h"
#include "3rdparty/rapidjson/document.h"
#include "3rdparty/rapidjson/filereadstream.h"

using namespace rapidjson;

typedef unsigned char byte;

class DataUnpacker : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int speed MEMBER speed NOTIFY dataChanged);
    Q_PROPERTY(int charge MEMBER charge NOTIFY dataChanged);
    Q_PROPERTY(int frontLeftTP MEMBER frontLeftTP NOTIFY dataChanged);
    Q_PROPERTY(int frontRightTP MEMBER frontRightTP NOTIFY dataChanged);
    Q_PROPERTY(int backLeftTP MEMBER backLeftTP NOTIFY dataChanged);
    Q_PROPERTY(int backRightTP MEMBER backRightTP NOTIFY dataChanged);

    Q_PROPERTY(bool leftTurn MEMBER leftTurn NOTIFY dataChanged);
    Q_PROPERTY(bool rightTurn MEMBER rightTurn NOTIFY dataChanged);

    Q_PROPERTY(float solarPower MEMBER solarPower NOTIFY dataChanged);
    Q_PROPERTY(float batteryVoltage MEMBER batteryVoltage NOTIFY dataChanged);
    Q_PROPERTY(float batteryCurrent MEMBER batteryCurrent NOTIFY dataChanged);
    Q_PROPERTY(float batteryPower MEMBER batteryPower NOTIFY dataChanged);
    Q_PROPERTY(float motorPower MEMBER motorPower NOTIFY dataChanged);
    Q_PROPERTY(float batteryTemp MEMBER batteryTemp NOTIFY dataChanged);
    Q_PROPERTY(float motorTemp MEMBER motorTemp NOTIFY dataChanged);
    Q_PROPERTY(float motorControllerTemp MEMBER motorControllerTemp NOTIFY dataChanged);
    // NOTE: char data is displayed as its ASCII decimal value, not the character, so QString is used instead
    Q_PROPERTY(QString state MEMBER state NOTIFY dataChanged);
public:
    //explicit DataUnpacker(std::vector<float> &floatData, std::vector<char> &charData, std::vector<uint8_t> &boolData, std::vector<uint8_t> &uint8_tData, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent = nullptr);
    explicit DataUnpacker(QObject *parent = nullptr);
    ~DataUnpacker();

    void unpack();
public slots:
    /*void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

    void threadProcedure();
    void startThread();*/
signals:
    void getData();
    void dataChanged();
    //void dataReady();
private:
    QThread dataHandlingThread;

    // TOOD Include only the properties that need to be displayed on the driver dashboard
    uint8_t speed, charge, frontLeftTP, frontRightTP, backLeftTP, backRightTP;
    float solarPower, batteryVoltage, batteryCurrent, batteryPower, motorPower, batteryTemp, motorTemp, motorControllerTemp;
    bool bpsFault, eStop, cruiseControl, leftTurn, rightTurn;
    QString state;

    //QTcpServer _server;
    //QList<QTcpSocket*> _sockets;

    //double time;

    QByteArray bytes;

    std::vector<float> floatData;
    std::vector<char> charData;
    std::vector<uint8_t> boolData; // It didn't like passing a bool to bytesToSomethingNotDouble for some reason
    std::vector<uint8_t> uint8_tData;
    std::vector<std::string> names;
    std::vector<int> byteNums;
    std::vector<uint8_t> sizes; // TODO
    std::vector<std::string> types;
/*
    std::vector<float> &floatData;
    std::vector<char> &charData;
    std::vector<uint8_t> &boolData; // It didn't like passing a bool to bytesToSomethingNotDouble for some reason
    std::vector<uint8_t> &uint8_tData;
    std::vector<std::string> &names;
    std::vector<int> byteNums;
    std::vector<std::string> &types;*/
};


#endif //DATAGENERATOR_DATAUNPACKER_H
