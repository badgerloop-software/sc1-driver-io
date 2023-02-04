//
// Created by Mingcan Li on 1/22/23.
//

#ifndef TELEMETRYLIB_DTI_H
#define TELEMETRYLIB_DTI_H

#include <QtCore>
#include <QtNetwork>
#include <cstdarg>

class DTI : public QObject{
    Q_OBJECT
public:
    /**
     * Send bytes via channel to be implemented, do not record data in this function.
     * @param bytes literally.
     */
    virtual void sendData(const char* bytes) = 0;
    /**
     * Receive bytes via channel to be implemented
     * @param max Maximum bytes to be received
     * @return bytes received
     */
    virtual const char* receiveData(int max) = 0;
    /**
     * @return connection status
     */
    virtual bool getConnectionStatus() = 0;
signals:
    void connectionStatusChanged() ;

public slots:
    virtual void onNewConnection() {};
    virtual void onSocketStatChanged(QAbstractSocket::SocketState state) {};
};

#endif //TELEMETRY
// LIB_DMIF_H
