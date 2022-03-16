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
    Q_PROPERTY(int fan_speed MEMBER fan_speed NOTIFY dataChanged);
    Q_PROPERTY(int tstamp_hr MEMBER tstamp_hr NOTIFY dataChanged);
    Q_PROPERTY(int tstamp_mn MEMBER tstamp_mn NOTIFY dataChanged);
    Q_PROPERTY(int tstamp_sc MEMBER tstamp_sc NOTIFY dataChanged);
    Q_PROPERTY(int tstamp_ms MEMBER tstamp_ms NOTIFY dataChanged);

    Q_PROPERTY(bool left_turn MEMBER left_turn NOTIFY dataChanged);
    Q_PROPERTY(bool right_turn MEMBER right_turn NOTIFY dataChanged);
    Q_PROPERTY(bool cruise MEMBER cruise NOTIFY dataChanged);
    // Shutdown circuit
    Q_PROPERTY(bool battery_eStop MEMBER battery_eStop NOTIFY dataChanged);
    Q_PROPERTY(bool driver_eStop MEMBER driver_eStop NOTIFY dataChanged);
    Q_PROPERTY(bool external_eStop MEMBER external_eStop NOTIFY dataChanged);
    Q_PROPERTY(bool crash MEMBER crash NOTIFY dataChanged);
    Q_PROPERTY(bool door MEMBER door NOTIFY dataChanged);
    Q_PROPERTY(bool mcu_check MEMBER mcu_check NOTIFY dataChanged);
    Q_PROPERTY(bool imd_status MEMBER imd_status NOTIFY dataChanged);

    Q_PROPERTY(float accelerator MEMBER accelerator NOTIFY dataChanged);
    Q_PROPERTY(float soc MEMBER soc NOTIFY dataChanged);
    Q_PROPERTY(float mppt_current_out MEMBER mppt_current_out NOTIFY dataChanged);
    Q_PROPERTY(float pack_voltage MEMBER pack_voltage NOTIFY dataChanged);
    Q_PROPERTY(float pack_current MEMBER pack_current NOTIFY dataChanged);
    Q_PROPERTY(float pack_temp MEMBER pack_temp NOTIFY dataChanged);
    Q_PROPERTY(float motor_temp MEMBER motor_temp NOTIFY dataChanged);
    Q_PROPERTY(float string1_temp MEMBER string1_temp NOTIFY dataChanged);
    Q_PROPERTY(float string2_temp MEMBER string2_temp NOTIFY dataChanged);
    Q_PROPERTY(float string3_temp MEMBER string3_temp NOTIFY dataChanged);

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
    uint8_t speed, fan_speed, tstamp_hr, tstamp_mn, tstamp_sc;
    uint16_t tstamp_ms;
    float accelerator, soc, mppt_current_out, pack_voltage, pack_current, pack_temp, motor_temp, string1_temp, string2_temp, string3_temp;
    bool bps_fault, cruise, left_turn, right_turn, driver_eStop, battery_eStop, external_eStop, crash, door, mcu_check, imd_status;
    QString state;

    QByteArray bytes;

    std::vector<std::string> names;
    std::vector<int> byteNums;
    std::vector<std::string> types;
};


#endif //DATAGENERATOR_DATAUNPACKER_H
