//
// Created by Mingcan Li on 2/23/23.
//

#ifndef TELEMETRYLIB_DATARESEND_H
#define TELEMETRYLIB_DATARESEND_H


#include <QObject>
#include "DTI.h"
class DataResend : QObject{
    Q_OBJECT
public:
    void setChannel(DTI *channel);
    void addToQueue(QByteArray arr);
    /*
     * IMPORTANT, tell the class if the telemetry class is connected/disconnected
     * before giving this class the data
     */
    void comStatus(bool state);
    bool isBusy(){return busy;}
protected:
    void resend();
signals:
    void send(QByteArray arr);
private:
    DTI *channel;
    QQueue<QByteArray> q;
    QMutex mutex;
    std::thread* t;
    std::atomic<bool> comstate, busy;
};


#endif //TELEMETRYLIB_DATARESEND_H
