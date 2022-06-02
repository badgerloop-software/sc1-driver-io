//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAPROCESSOR_DATAUNPACKER_H
#define DATAPROCESSOR_DATAUNPACKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
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
    Q_PROPERTY(bool hazards MEMBER hazards NOTIFY dataChanged);
    Q_PROPERTY(bool headlights MEMBER headlights NOTIFY dataChanged);
    Q_PROPERTY(bool cruise MEMBER cruise NOTIFY dataChanged);
    Q_PROPERTY(bool mainIO_heartbeat MEMBER mainIO_heartbeat NOTIFY dataChanged);
    Q_PROPERTY(bool eng_dash_commfail MEMBER eng_dash_commfail NOTIFY dataChanged);

    // Shutdown circuit
    Q_PROPERTY(bool battery_eStop MEMBER battery_eStop NOTIFY dataChanged);
    Q_PROPERTY(bool driver_eStop MEMBER driver_eStop NOTIFY dataChanged);
    Q_PROPERTY(bool external_eStop MEMBER external_eStop NOTIFY dataChanged);
    Q_PROPERTY(bool crash MEMBER crash NOTIFY dataChanged);
    Q_PROPERTY(bool door MEMBER door NOTIFY dataChanged);
    Q_PROPERTY(bool mcu_check MEMBER mcu_check NOTIFY dataChanged);
    Q_PROPERTY(bool imd_status MEMBER imd_status NOTIFY dataChanged);
    Q_PROPERTY(bool mps_enable MEMBER mps_enable NOTIFY dataChanged);
    Q_PROPERTY(bool bms_canbus_failure MEMBER bms_canbus_failure NOTIFY dataChanged);
    Q_PROPERTY(bool voltage_failsafe MEMBER voltage_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool current_failsafe MEMBER current_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool supply_power_failsafe MEMBER supply_power_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool memory_failsafe MEMBER memory_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool relay_failsafe MEMBER relay_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool bps_fault MEMBER bps_fault NOTIFY dataChanged);
    // Not in the data format, but shared with controls
    Q_PROPERTY(bool restart_enable MEMBER restart_enable NOTIFY dataChanged);

    Q_PROPERTY(float accelerator MEMBER accelerator NOTIFY dataChanged);
    Q_PROPERTY(float soc MEMBER soc NOTIFY dataChanged);
    Q_PROPERTY(float mppt_current_out MEMBER mppt_current_out NOTIFY dataChanged);
    Q_PROPERTY(float pack_voltage MEMBER pack_voltage NOTIFY dataChanged);
    Q_PROPERTY(float pack_current MEMBER pack_current NOTIFY dataChanged);
    Q_PROPERTY(float pack_temp MEMBER pack_temp NOTIFY dataChanged);
    Q_PROPERTY(float bms_input_voltage MEMBER bms_input_voltage NOTIFY dataChanged);
    Q_PROPERTY(float motor_temp MEMBER motor_temp NOTIFY dataChanged);
    Q_PROPERTY(float driverIO_temp MEMBER driverIO_temp NOTIFY dataChanged);
    Q_PROPERTY(float mainIO_temp MEMBER mainIO_temp NOTIFY dataChanged);
    Q_PROPERTY(float cabin_temp MEMBER cabin_temp NOTIFY dataChanged);
    Q_PROPERTY(float string1_temp MEMBER string1_temp NOTIFY dataChanged);
    Q_PROPERTY(float string2_temp MEMBER string2_temp NOTIFY dataChanged);
    Q_PROPERTY(float string3_temp MEMBER string3_temp NOTIFY dataChanged);

    // NOTE: char data is displayed as its ASCII decimal value, not the character, so QString is used instead
    Q_PROPERTY(QString state MEMBER state NOTIFY dataChanged);

    Q_PROPERTY(QVector<float> cell_group_voltages MEMBER cell_group_voltages NOTIFY dataChanged);

public:
    explicit DataUnpacker(QObject *parent = nullptr);
    ~DataUnpacker();
public slots:
    void unpack();
    void eng_dash_connection(bool state);
signals:
    void getData();
    void dataChanged();
    void enableRestart();
private:
    QThread dataHandlingThread;

    // TOOD Include only the properties that need to be displayed on the driver dashboard
    uint8_t speed, fan_speed, tstamp_hr, tstamp_mn, tstamp_sc;
    uint16_t tstamp_ms;
    float accelerator, soc, mppt_current_out, pack_voltage, pack_current, pack_temp, motor_temp, driverIO_temp, mainIO_temp, cabin_temp, string1_temp, string2_temp, string3_temp;
    bool headlights, cruise, left_turn, right_turn, hazards, mainIO_heartbeat;
    QString state;
    // Data for shutdown circuit
    bool driver_eStop, battery_eStop, external_eStop, crash, door, mcu_check, imd_status, mps_enable, bps_fault, bms_canbus_failure, voltage_failsafe, current_failsafe, supply_power_failsafe, memory_failsafe, relay_failsafe, bms_input_voltage, restart_enable, eng_dash_commfail=1;
    QVector<float> cell_group_voltages;

    int cell_group_voltages_begin, cell_group_voltages_end; // First and last indices of the cell group voltages in data format

    QByteArray bytes;

    std::vector<std::string> names;
    std::vector<int> byteNums;
    std::vector<std::string> types;
    QMutex mutex;
};


#endif //DATAGENERATOR_DATAUNPACKER_H
