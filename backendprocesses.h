#ifndef BACKENDPROCESSES_H
#define BACKENDPROCESSES_H

#include <QObject>


class BackendProcesses : public QObject
{
    Q_OBJECT

public:
    explicit BackendProcesses(QObject *parent = nullptr);

signals:

private:
    //1 byte stuffs
    int8_t speed, charge, fltp, frtp, bltp, brtp;
    char state;
    bool bpsFault, eStop, cruiseControl, leftTurn, rightTurn;
    //4 byte stuffs
    float soloarPower, battteryVoltage, batteryCurrent, motorPower,batteryTemp,motorTemp,
    motorControllorTemp,bat1, bat2, bat3, bat4;
};

#endif // BACKENDPROCESSES_H
