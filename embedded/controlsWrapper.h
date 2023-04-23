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
};

class controlsWrapper : public QObject
{
    Q_OBJECT
    public:
        explicit controlsWrapper(QByteArray &bytes, QMutex &mutex, std::atomic<bool> &restart_enable, controlsOffsets offsets, QObject *parent = nullptr);
    public slots:
        void startThread();
        // need other slot for a signal
    private:
        QByteArray &bytes;
        QMutex &mutex;
        std::atomic<bool> &restart_enable;
};

#endif
