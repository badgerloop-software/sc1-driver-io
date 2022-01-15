#ifndef BACKENDPROCESSES_H
#define BACKENDPROCESSES_H

#include <QObject>
#include <QThread>
#include "DataProcessor/UnpackedData.h"
#include "DataProcessor/DataUnpacker.h"


class BackendProcesses : public QObject
{
    Q_OBJECT

    Q_PROPERTY(uint8_t speed MEMBER speed NOTIFY speedChanged);
    Q_PROPERTY(uint8_t charge MEMBER charge NOTIFY chargeChanged);
    Q_PROPERTY(uint8_t flTp MEMBER flTp NOTIFY flTpChanged);
    Q_PROPERTY(uint8_t frTp MEMBER frTp NOTIFY frTpChanged);
    Q_PROPERTY(uint8_t rlTp MEMBER rlTp NOTIFY rlTpChanged);
    Q_PROPERTY(uint8_t rrTp MEMBER rrTp NOTIFY rrTpChanged);

    Q_PROPERTY(float solarP MEMBER solarP NOTIFY solarPChanged);
    Q_PROPERTY(float netP MEMBER netP NOTIFY netPChanged);
    Q_PROPERTY(float motorP MEMBER motorP NOTIFY motorPChanged);
    Q_PROPERTY(float batteryT MEMBER batteryT NOTIFY batteryTChanged);
    Q_PROPERTY(float motorT MEMBER motorT NOTIFY motorTChanged);
    Q_PROPERTY(float motorControllerT MEMBER motorControllerT NOTIFY motorControllerTChanged);

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

    uint8_t speed, charge, flTp, frTp, rlTp, rrTp;
    float solarP, netP, motorP, batteryT, motorT, motorControllerT;
    bool bpsFault, eStop, cruise, lt, rt;
    char state;
};

#endif // BACKENDPROCESSES_H
