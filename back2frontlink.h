#ifndef BACK2FRONTLINK_H
#define BACK2FRONTLINK_H

#include <QObject>
#include "DataProcessor/DataGen.h"
#include "DataProcessor/DataUnpacker.h"

class Back2FrontLink : public QObject
{
    Q_OBJECT

public:
    explicit Back2FrontLink(QObject *parent = nullptr);

signals:
     void speedChanged();
public slots:
private:
    int speed=0, charge=0, flTp=0, frTp=0, rlTp=0, rrTp=0;
    double power, solarP, netP, motorP, batteryT, motorT, motorControllerT;
    DataGen *gen;
    DataUnpacker *unpacker;
};

#endif // BACK2FRONTLINK_H
