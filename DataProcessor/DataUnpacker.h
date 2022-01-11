//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAPROCESSOR_DATAUNPACKER_H
#define DATAPROCESSOR_DATAUNPACKER_H

#include <vector>
#include <QObject>
#include "DataGen.h"
#include "thread"
#include <unistd.h>

//using namespace std;
typedef unsigned char byte;

class DataUnpacker : public QObject{
    Q_OBJECT

    Q_PROPERTY(int speed MEMBER speed NOTIFY speedChanged);
    Q_PROPERTY(int charge MEMBER charge NOTIFY chargeChanged);
    Q_PROPERTY(int flTp MEMBER flTp NOTIFY flTpChanged);
    Q_PROPERTY(int frTp MEMBER frTp NOTIFY frTpChanged);
    Q_PROPERTY(int rlTp MEMBER rlTp NOTIFY rlTpChanged);
    Q_PROPERTY(int rrTp MEMBER rrTp NOTIFY rrTpChanged);

    Q_PROPERTY(double power MEMBER power NOTIFY powerChanged);
    Q_PROPERTY(double solarP MEMBER solarP NOTIFY solarPChanged);
    Q_PROPERTY(double netP MEMBER netP NOTIFY netPChanged);
    Q_PROPERTY(double motorP MEMBER motorP NOTIFY motorPChanged);
    Q_PROPERTY(double batteryT MEMBER batteryT NOTIFY batteryTChanged);
    Q_PROPERTY(double motorT MEMBER motorT NOTIFY motorTChanged);
    Q_PROPERTY(double motorControllerT MEMBER motorControllerT NOTIFY motorControllerTChanged);

    Q_PROPERTY(char state MEMBER state NOTIFY stateChanged);
public:
    explicit DataUnpacker(QObject *parent = nullptr);
    void unpack(std::vector<byte> rawData);
    void startThread();
signals:
    void speedChanged();
    void chargeChanged();
    void flTpChanged();
    void frTpChanged();
    void rlTpChanged();
    void rrTpChanged();

    void powerChanged();
    void solarPChanged();
    void netPChanged();
    void motorPChanged();
    void batteryTChanged();
    void motorTChanged();
    void motorControllerTChanged();

    void stateChanged();
private:
    void threadProcedure();
    int speed, charge, flTp, frTp, rlTp, rrTp;
    double power, solarP, netP, motorP, batteryT, motorT, motorControllerT;
    bool bpsFault, eStop, cruise, lt, rt;
    char state;
    std::thread t;
};


#endif //DATAGENERATOR_DATAUNPACKER_H
