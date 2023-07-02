#ifndef CONTROLSWRAPPER_H
#define CONTROLSWRAPPER_H

#include <QObject>
#include <QByteArray>
#include <QMutex>


struct controlsOffsets {
    int horn_status;
    int hazards;
    int headlights;
    int right_turn;
    int left_blinker;
    int bl_turn_led_en;
    int br_turn_led_en;
    int bc_brake_led_en;
    int bc_bps_led_en;
    int headlights_led_en;
    int fr_turn_led_en;
    int fl_turn_led_en;
    int driver_power_warning;
    int driver_power_critical;
    int driver_power_tc;
    int driver_power_valid;
    int driverIO_temp;
    int cabin_temp;
    int driver_vbus_current;
    int driver_5V_bus;
    int driver_12V_bus;
    int driver_vbus;
    int mainIO_heartbeat;
    int mcu_check;
    int bps_fault;
    int pack_temp;
    int pack_current;
    int pack_voltage;
    int lowest_cell_group_voltage;
    int highest_cell_group_voltage;
    int imd_status;
    int charge_enable;
    int discharge_enable;
    int voltage_failsafe;
    int external_eStop;
};

class controlsWrapper : public QObject
{
    Q_OBJECT
    public:
        explicit controlsWrapper(QByteArray &bytes, QMutex &mutex, std::atomic<bool> &restart_enable, controlsOffsets offsets, QObject *parent = nullptr);
        ~controlsWrapper();
    public slots:
        void mainProcess();
        // need other slot for a signal
    signals:
        void endMainProcess();
    private:
        std::atomic<bool> endControlsWrapper = false;
        int messages_not_received = 0;
        QByteArray &bytes;
        QMutex &mutex;
        controlsOffsets offsets;
        std::atomic<bool> &restart_enable;
};

#endif
