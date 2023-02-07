#ifndef TELEMETRYLIB_LIBRARY_H
#define TELEMETRYLIB_LIBRARY_H
#include <QtCore>
#include <QtNetwork>
#include <iostream>
#include <QTcpServer>
#include <vector>
#include "DTI.h"
#include <QDebug>

/**
 * A library built for handling data telemetry that allows automatic switch between communication methods with modular
 * design for future extension
 */

class Telemetry : public QObject{
    Q_OBJECT
public:
    /**
     *
     * @param com Data telemetry object ranked by priority
     * @param size
     */
    Telemetry();
    Telemetry(std::vector<DTI*> comm);
    void sendData(QByteArray data);
    const char* receiveData();
    void helloworld();
signals:
    void eng_dash_connection(bool state);
public slots:
    void comChannelChanged();
private:
    std::atomic<int> commChannel = -1;
    std::vector <DTI*> comm;
};
#endif //TELEMETRYLIB_LIBRARY_H
