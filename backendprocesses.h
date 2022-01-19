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
    // Qml didn't want to play nice with uint8_t on the pi, so I switched it to int
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
    explicit BackendProcesses(QObject *parent = nullptr);
    ~BackendProcesses(); // TODO
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
    // TODO DataUnpacker* unpacker;
    unpackedData data;
    // TOOD Include only the properties that need to be displayed on the driver dashboard
    // TODO Remove these
    uint8_t speed, charge, frontLeftTP, frontRightTP, backLeftTP, backRightTP;
    float solarPower, batteryVoltage, batteryCurrent, batteryPower, motorPower, batteryTemp, motorTemp, motorControllerTemp;
    bool bpsFault, eStop, cruiseControl, leftTurn, rightTurn;
    QString state;

    std::vector<float> floatData;
    std::vector<char> charData;
    std::vector<uint8_t> boolData; // TODO It didn't like passing a bool to bytesToSomethingNotDouble for some reason
    std::vector<uint8_t> uint8_tData;
    std::vector<std::string> names;
    std::vector<uint8_t> sizes;
    std::vector<std::string> types;

};

#endif // BACKENDPROCESSES_H
