#ifndef BACKENDPROCESSES_H
#define BACKENDPROCESSES_H

#include <QObject>
#include "DataProcessor/UnpackedData.h"
#include "DataProcessor/DataUnpacker.h"


class BackendProcesses : public QObject
{
    Q_OBJECT

    /*Q_PROPERTY(int speed MEMBER speed NOTIFY speedChanged);
    Q_PROPERTY(int charge MEMBER charge NOTIFY chargeChanged);
    Q_PROPERTY(int flTp MEMBER flTp NOTIFY flTpChanged);
    Q_PROPERTY(int frTp MEMBER frTp NOTIFY frTpChanged);
    Q_PROPERTY(int rlTp MEMBER rlTp NOTIFY rlTpChanged);
    Q_PROPERTY(int rrTp MEMBER rrTp NOTIFY rrTpChanged);

    //Q_PROPERTY(double power MEMBER power NOTIFY powerChanged);
    Q_PROPERTY(double solarP MEMBER solarP NOTIFY solarPChanged);
    Q_PROPERTY(double netP MEMBER netP NOTIFY netPChanged);
    Q_PROPERTY(double motorP MEMBER motorP NOTIFY motorPChanged);
    Q_PROPERTY(double batteryT MEMBER batteryT NOTIFY batteryTChanged);
    Q_PROPERTY(double motorT MEMBER motorT NOTIFY motorTChanged);
    Q_PROPERTY(double motorControllerT MEMBER motorControllerT NOTIFY motorControllerTChanged);

    // TODO Maybe use READ and have an accessor method that also appends '\0' to it (or could just append '\0' to it in the qml file)
    Q_PROPERTY(char state MEMBER state NOTIFY stateChanged);*/

    Q_PROPERTY(int speed MEMBER speed NOTIFY speedChanged);
    Q_PROPERTY(int charge MEMBER charge NOTIFY chargeChanged);
    Q_PROPERTY(int flTp MEMBER flTp NOTIFY flTpChanged);
    Q_PROPERTY(int frTp MEMBER frTp NOTIFY frTpChanged);
    Q_PROPERTY(int rlTp MEMBER rlTp NOTIFY rlTpChanged);
    Q_PROPERTY(int rrTp MEMBER rrTp NOTIFY rrTpChanged);

    Q_PROPERTY(double solarP MEMBER solarP NOTIFY solarPChanged);
    Q_PROPERTY(double netP MEMBER netP NOTIFY netPChanged);
    Q_PROPERTY(double motorP MEMBER motorP NOTIFY motorPChanged);
    Q_PROPERTY(double batteryT MEMBER batteryT NOTIFY batteryTChanged);
    Q_PROPERTY(double motorT MEMBER motorT NOTIFY motorTChanged);
    Q_PROPERTY(double motorControllerT MEMBER motorControllerT NOTIFY motorControllerTChanged);

    // TODO Maybe use READ and have an accessor method that also appends '\0' to it (or could just append '\0' to it in the qml file)
    Q_PROPERTY(char state MEMBER state NOTIFY stateChanged);

public:
    explicit BackendProcesses(QObject *parent = nullptr);
    //~BackendProcesses();
public slots:
    void handleData();
signals:
    void getData();

    void speedChanged();
    void chargeChanged();
    void flTpChanged();
    void frTpChanged();
    void rlTpChanged();
    void rrTpChanged();

    void solarPChanged();
    void netPChanged();
    void motorPChanged();
    void batteryTChanged();
    void motorTChanged();
    void motorControllerTChanged();

    void stateChanged();
private:
    QThread dataHandlingThread;
    DataUnpacker* unpacker;
    unpackedData data;

    int speed, charge, flTp, frTp, rlTp, rrTp;
    float solarP, netP, motorP, batteryT, motorT, motorControllerT;
    bool bpsFault, eStop, cruise, lt, rt;
    char state;

    /*
    //1 byte stuffs
    int8_t speed, charge, fltp, frtp, bltp, brtp;
    char state;
    bool bpsFault, eStop, cruiseControl, leftTurn, rightTurn;
    //4 byte stuffs
    float soloarPower, battteryVoltage, batteryCurrent, motorPower,batteryTemp,motorTemp,
    motorControllorTemp,bat1, bat2, bat3, bat4; */
};

#endif // BACKENDPROCESSES_H
