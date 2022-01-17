#ifndef BACKENDPROCESSES_H
#define BACKENDPROCESSES_H

#include <QObject>
#include <QThread>
#include "DataProcessor/UnpackedData.h"
#include "DataProcessor/DataUnpacker.h"


class BackendProcesses : public QObject
{
    Q_OBJECT

    /* TODO
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
    */
    // TODO Include only the properties that need to be displayed on the driver dashboard
    Q_PROPERTY(uint8_t speed MEMBER speed NOTIFY dataChanged);
    Q_PROPERTY(uint8_t charge MEMBER charge NOTIFY dataChanged);
    Q_PROPERTY(uint8_t flTp MEMBER flTp NOTIFY dataChanged);
    Q_PROPERTY(uint8_t frTp MEMBER frTp NOTIFY dataChanged);
    Q_PROPERTY(uint8_t rlTp MEMBER rlTp NOTIFY dataChanged);
    Q_PROPERTY(uint8_t rrTp MEMBER rrTp NOTIFY dataChanged);

    Q_PROPERTY(float solarP MEMBER solarP NOTIFY dataChanged);
    Q_PROPERTY(float netP MEMBER netP NOTIFY dataChanged);
    Q_PROPERTY(float motorP MEMBER motorP NOTIFY dataChanged);
    Q_PROPERTY(float batteryT MEMBER batteryT NOTIFY dataChanged);
    Q_PROPERTY(float motorT MEMBER motorT NOTIFY dataChanged);
    Q_PROPERTY(float motorControllerT MEMBER motorControllerT NOTIFY dataChanged);

    Q_PROPERTY(char state MEMBER state NOTIFY dataChanged);
public:
    explicit BackendProcesses(QObject *parent = nullptr);
    //~BackendProcesses();
public slots:
    void handleData();
signals:
    void getData();

    /* TODO
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

    void stateChanged();*/
    void dataChanged();
private:
    QThread dataHandlingThread;
    DataUnpacker* unpacker;
    unpackedData data;
    // TOOD Include only the properties that need to be displayed on the driver dashboard
    // TODO Remove these
    uint8_t speed, charge, flTp, frTp, rlTp, rrTp;
    float solarP, netP, motorP, batteryT, motorT, motorControllerT;
    bool bpsFault, eStop, cruise, lt, rt;
    char state;

    std::vector<float> floatData;
    std::vector<char> charData;
    std::vector<bool> boolData;
    std::vector<uint8_t> uint8_tData;
    std::vector<std::string> names;
    std::vector<uint8_t> sizes;
    std::vector<std::string> types; // TODO Remove; this should only be in DataUnpacker

};

#endif // BACKENDPROCESSES_H
