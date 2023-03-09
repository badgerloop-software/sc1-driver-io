//
// Created by Mingcan Li on 1/22/23.
//

#ifndef TELEMETRYLIB_DTI_H
#define TELEMETRYLIB_DTI_H

#include <QtCore>
#include <QtNetwork>

class DTI : public QObject{
    Q_OBJECT
public:
    /* nope
    /**
     * Receive bytes via channel to be implemented
     * @return bytes received
     */
    //virtual std::string receiveData() = 0;
    /**
     * @return connection status
     */
    virtual bool getConnectionStatus() = 0;

signals:
    /**
     * for notifying telemetry class to redo polling.
     */
    void connectionStatusChanged();

public slots:
    /**
     * Send bytes via channel to be implemented, do not record data in this function.
     * @param bytes literally.
     */
    virtual void sendData(QByteArray bytes) = 0;
    //if inheritance instance needs slots, add them here as a VIRTUAL function, otherwise there will be a stupid vtable error
    virtual void onNewConnection() {};
    virtual void onSocketStateChanged(QAbstractSocket::SocketState state) {};
    virtual void readReply() {};
};

#endif //TELEMETRY
// LIB_DMIF_H
