#ifndef BACKENDPROCESSES_H
#define BACKENDPROCESSES_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <unistd.h>
//#include <QThread>
//#include "DataProcessor/DataUnpacker.h"
#include "DataProcessor/DataGen.h"


class BackendProcesses : public QObject
{
    Q_OBJECT

    // TODO Include only the properties that need to be displayed on the driver dashboard
    // Qml didn't want to play nice with uint8_t on the pi, so I switched it to int
    /*Q_PROPERTY(int speed MEMBER speed NOTIFY dataChanged);
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
    Q_PROPERTY(QString state MEMBER state NOTIFY dataChanged);*/
public:
    //explicit BackendProcesses(QObject *parent = nullptr);
    explicit BackendProcesses(QByteArray &bytes, std::vector<float> &floatData, std::vector<char> &charData, std::vector<uint8_t> &boolData, std::vector<uint8_t> &uint8_tData, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent = nullptr);
    //~BackendProcesses();
public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

    void threadProcedure();
    void startThread();

    //void handleData();
signals:
    void dataReady();
    //void getData();
    //void dataChanged();
private:
    //QThread dataHandlingThread;

    /*// TOOD Include only the properties that need to be displayed on the driver dashboard
    uint8_t speed, charge, frontLeftTP, frontRightTP, backLeftTP, backRightTP;
    float solarPower, batteryVoltage, batteryCurrent, batteryPower, motorPower, batteryTemp, motorTemp, motorControllerTemp;
    bool bpsFault, eStop, cruiseControl, leftTurn, rightTurn;
    QString state;*/

    QTcpServer _server;
    QList<QTcpSocket*> _sockets;

    double time;

    QByteArray &bytes;

    std::vector<float> &floatData;
    std::vector<char> &charData;
    std::vector<uint8_t> &boolData; // It didn't like passing a bool to bytesToSomethingNotDouble for some reason
    std::vector<uint8_t> &uint8_tData;
    std::vector<std::string> &names;
    std::vector<int> byteNums;
    std::vector<std::string> &types;

    /*std::vector<float> floatData;
    std::vector<char> charData;
    std::vector<uint8_t> boolData; // It didn't like passing a bool to bytesToSomethingNotDouble for some reason
    std::vector<uint8_t> uint8_tData;
    std::vector<std::string> names;
    std::vector<uint8_t> sizes;
    std::vector<std::string> types;*/
};

#endif // BACKENDPROCESSES_H
