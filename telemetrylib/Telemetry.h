#ifndef TELEMETRYLIB_LIBRARY_H
#define TELEMETRYLIB_LIBRARY_H
#include <QtCore>
#include <QtNetwork>
#include <iostream>
#include <QTcpServer>
#include <vector>
#include "DTI.h"
#include <QDebug>
#include "DataResend.h"
/**
 * A library built for handling data telemetry that allows automatic switching
 * between communication methods with modular design for future extension
 */

class Telemetry : public QObject{
    Q_OBJECT
public:
    Telemetry();
    /**
     * @param com Data telemetry object ranked by priority
     * @param size
     */
    Telemetry(std::vector<DTI*> comm);
    /**
     * to send data, as simple as it gets
     * @param data
     * @param timestamp the time which the byte array is created
     */
    void sendData(QByteArray data, long long timestamp);
    /* NVM
     * receive data from telemetry
     * @return data
     */
    /*
    std::string receiveData();
    */
signals:
    void eng_dash_connection(bool state);
public slots:
    void comChannelChanged();
private:
    int originalSize = 0;
    int compressedSize = 0;
    DataResend resendQueue;
    std::vector<QByteArray> dataCache;
    std::atomic<int> commChannel = -1;
    std::vector <DTI*> comm;
};
#endif //TELEMETRYLIB_LIBRARY_H
