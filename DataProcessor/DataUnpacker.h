//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAPROCESSOR_DATAUNPACKER_H
#define DATAPROCESSOR_DATAUNPACKER_H

#include <QObject>
#include <QThread>
#include "backendprocesses.h"
#include "3rdparty/rapidjson/document.h"
#include "3rdparty/rapidjson/filereadstream.h"

using namespace rapidjson;

class DataUnpacker : public QObject
{
    Q_OBJECT

    // Include only the properties that need to be displayed on the driver dashboard
    // Qml didn't want to play nice with uint8_t on the pi, so now it's int
    Q_PROPERTY(int speed MEMBER speed NOTIFY dataChanged);

    Q_PROPERTY(bool left_turn MEMBER left_turn NOTIFY dataChanged);
    Q_PROPERTY(bool right_turn MEMBER right_turn NOTIFY dataChanged);
    Q_PROPERTY(bool cruise MEMBER cruise NOTIFY dataChanged);

    Q_PROPERTY(float soc MEMBER soc NOTIFY dataChanged);
    Q_PROPERTY(float mppt_current_out MEMBER mppt_current_out NOTIFY dataChanged);
    Q_PROPERTY(float pack_voltage MEMBER pack_voltage NOTIFY dataChanged);
    Q_PROPERTY(float pack_current MEMBER pack_current NOTIFY dataChanged);
    Q_PROPERTY(float pack_temp MEMBER pack_temp NOTIFY dataChanged);
    Q_PROPERTY(float motor_temp MEMBER motor_temp NOTIFY dataChanged);
    // NOTE: char data is displayed as its ASCII decimal value, not the character, so QString is used instead
    Q_PROPERTY(QString state MEMBER state NOTIFY dataChanged);
public:
    explicit DataUnpacker(QObject *parent = nullptr);
    ~DataUnpacker();
public slots:
    void unpack();
signals:
    void getData();
    void dataChanged();
private:
    QThread dataHandlingThread;

    // TOOD Include only the properties that need to be displayed on the driver dashboard
    uint8_t speed;
    float soc, mppt_current_out, pack_voltage, pack_current, pack_temp, motor_temp;
    bool bps_fault, driver_eStop, cruise, left_turn, right_turn;
    QString state;

    QByteArray bytes;

    std::vector<std::string> names;
    std::vector<int> byteNums;
    std::vector<std::string> types;
};


#endif //DATAGENERATOR_DATAUNPACKER_H
