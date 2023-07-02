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
#include "embedded/controlsWrapper.h"

using namespace rapidjson;

class DataUnpacker : public QObject
{
    Q_OBJECT

    // Include only the properties that need to be displayed on the driver dashboard
    // Qml didn't want to play nice with uint8_t on the pi, so now it's int
    Q_PROPERTY(int fan_speed MEMBER fan_speed NOTIFY dataChanged);
    Q_PROPERTY(int tstamp_hr MEMBER tstamp_hr NOTIFY dataChanged);
    Q_PROPERTY(int tstamp_mn MEMBER tstamp_mn NOTIFY dataChanged);
    Q_PROPERTY(int tstamp_sc MEMBER tstamp_sc NOTIFY dataChanged);
    Q_PROPERTY(int tstamp_ms MEMBER tstamp_ms NOTIFY dataChanged);

    Q_PROPERTY(bool left_turn MEMBER left_turn NOTIFY dataChanged);
    Q_PROPERTY(bool right_turn MEMBER right_turn NOTIFY dataChanged);
    Q_PROPERTY(bool hazards MEMBER hazards NOTIFY dataChanged);
    Q_PROPERTY(bool headlights MEMBER headlights NOTIFY dataChanged);
    Q_PROPERTY(bool mainIO_heartbeat MEMBER mainIO_heartbeat NOTIFY dataChanged);
    Q_PROPERTY(bool eng_dash_commfail MEMBER eng_dash_commfail NOTIFY dataChanged);
    Q_PROPERTY(bool crz_pwr_mode MEMBER crz_pwr_mode NOTIFY dataChanged)
    Q_PROPERTY(bool crz_spd_mode MEMBER crz_spd_mode NOTIFY dataChanged)

    // Shutdown circuit
    Q_PROPERTY(bool driver_eStop MEMBER driver_eStop NOTIFY dataChanged);
    Q_PROPERTY(bool external_eStop MEMBER external_eStop NOTIFY dataChanged);
    Q_PROPERTY(bool crash MEMBER crash NOTIFY dataChanged);
    Q_PROPERTY(bool door MEMBER door NOTIFY dataChanged);
    Q_PROPERTY(bool mcu_check MEMBER mcu_check NOTIFY dataChanged);
    Q_PROPERTY(bool imd_status MEMBER imd_status NOTIFY dataChanged);
    Q_PROPERTY(bool discharge_enable MEMBER discharge_enable NOTIFY dataChanged);
    Q_PROPERTY(bool low_contactor MEMBER low_contactor NOTIFY dataChanged);
    Q_PROPERTY(bool bms_can_heartbeat MEMBER bms_can_heartbeat NOTIFY dataChanged);
    Q_PROPERTY(bool voltage_failsafe MEMBER voltage_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool current_failsafe MEMBER current_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool input_power_supply_failsafe MEMBER input_power_supply_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool relay_failsafe MEMBER relay_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool cell_balancing_active MEMBER cell_balancing_active NOTIFY dataChanged);
    Q_PROPERTY(bool charge_interlock_failsafe MEMBER charge_interlock_failsafe NOTIFY dataChanged);
    Q_PROPERTY(bool thermistor_b_value_table_invalid MEMBER thermistor_b_value_table_invalid NOTIFY dataChanged);
    Q_PROPERTY(bool charge_enable MEMBER charge_enable NOTIFY dataChanged);
    Q_PROPERTY(bool bps_fault MEMBER bps_fault NOTIFY dataChanged);
    Q_PROPERTY(bool dcdc_valid MEMBER dcdc_valid NOTIFY dataChanged);
    Q_PROPERTY(bool supplemental_valid MEMBER supplemental_valid NOTIFY dataChanged);
    Q_PROPERTY(bool mcu_hv_en MEMBER mcu_hv_en NOTIFY dataChanged);
    Q_PROPERTY(bool mcu_stat_fdbk MEMBER mcu_stat_fdbk NOTIFY dataChanged);
    Q_PROPERTY(bool parking_brake MEMBER parking_brake NOTIFY dataChanged);
    Q_PROPERTY(bool eco MEMBER eco NOTIFY dataChanged);
    Q_PROPERTY(bool main_telem MEMBER main_telem NOTIFY dataChanged);
    Q_PROPERTY(int mc_status MEMBER mc_status NOTIFY dataChanged);
    // Not in the data format, but shared with controls
    Q_PROPERTY(bool restart_enable MEMBER restart_enable NOTIFY dataChanged);

    Q_PROPERTY(float speed MEMBER speed NOTIFY dataChanged);
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
    Q_PROPERTY(float motor_controller_temp MEMBER motor_controller_temp NOTIFY dataChanged);
    Q_PROPERTY(float cabin_temp MEMBER cabin_temp NOTIFY dataChanged);
    Q_PROPERTY(float string1_temp MEMBER string1_temp NOTIFY dataChanged);
    Q_PROPERTY(float string2_temp MEMBER string2_temp NOTIFY dataChanged);
    Q_PROPERTY(float string3_temp MEMBER string3_temp NOTIFY dataChanged);
    Q_PROPERTY(float crz_pwr_setpt MEMBER crz_pwr_setpt NOTIFY dataChanged);
    Q_PROPERTY(float crz_spd_setpt MEMBER crz_spd_setpt NOTIFY dataChanged);
    Q_PROPERTY(float supplemental_voltage MEMBER supplemental_voltage NOTIFY dataChanged);
    Q_PROPERTY(float est_supplemental_soc MEMBER est_supplemental_soc NOTIFY dataChanged);
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
    void setMcuHvEn(bool state);
private:
    bool checkRestartEnable();

    QThread dataHandlingThread;
    QThread controlsThread;

    // TODO Include only the properties that need to be displayed on the driver dashboard
    uint8_t fan_speed, tstamp_hr, tstamp_mn, tstamp_sc;
    uint16_t tstamp_ms;
    float speed, accelerator, crz_spd_setpt, crz_pwr_setpt;
    float soc, est_supplemental_soc;
    float mppt_current_out;
    float pack_voltage, pack_current, supplemental_voltage;
    float pack_temp, motor_temp, driverIO_temp, mainIO_temp, cabin_temp, motor_controller_temp;
    float string1_temp, string2_temp, string3_temp;
    bool headlights, left_turn, right_turn, hazards, mainIO_heartbeat, crz_pwr_mode, crz_spd_mode, eco, main_telem, parking_brake;
    bool eng_dash_commfail=1;
    QString state;
    // Data for shutdown circuit
    // TODO Check initial values (should be nominal values, except for contactors, which should be open/false during restart)
    float bms_input_voltage;
    bool driver_eStop=false, external_eStop=false;
    bool crash=false;
    bool door= false;
    bool mcu_check=false;
    bool imd_status=false;
    bool bps_fault=false;
    bool discharge_enable=false, charge_enable=false, bms_can_heartbeat=false;
    bool mcu_hv_en=false, mcu_stat_fdbk=false, dcdc_valid=false, supplemental_valid=false, mppt_contactor=false, low_contactor=false, motor_controller_contactor=false;
    bool voltage_failsafe=false, current_failsafe=false, relay_failsafe=false, cell_balancing_active=true, charge_interlock_failsafe=false, thermistor_b_value_table_invalid=false, input_power_supply_failsafe=false;
    std::atomic<bool> restart_enable=true;
    QVector<float> cell_group_voltages;
    int mc_status=0;


    int cell_group_voltages_begin, cell_group_voltages_end; // First and last indices of the cell group voltages in data format

    QByteArray bytes;

    std::vector<std::string> names;
    std::vector<int> byteNums;
    std::vector<std::string> types;
    QMutex mutex;
};


#endif //DATAGENERATOR_DATAUNPACKER_H
