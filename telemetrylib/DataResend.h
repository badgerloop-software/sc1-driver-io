//
// Created by Mingcan Li on 2/23/23.
//

#ifndef TELEMETRYLIB_DATARESEND_H
#define TELEMETRYLIB_DATARESEND_H

#include <QObject>
#include "DTI.h"

/*
 * DataResend is used to store data during connection lost and resending data after
 * connection is regained.
 */

/*
 * Some more details:
 * Telemetry class detects the network disconnect and sets the DataResend into store
 * data mode by calling comStatus(False), then Telemetry class directs the data into
 * the Queue of this class. after connection is regained, the Telemetry class notifies
 * this class to resented using comStatus(True), a thread is created to resend the Data
 * and isBusy() returns true, which stops Telemetry from sending data and instead add
 * new data into resend Queue.
 *
 */

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
