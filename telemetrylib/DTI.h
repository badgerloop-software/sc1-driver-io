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
    virtual void sendData() = 0;
    virtual char* receiveData() = 0;
    virtual bool getConnectionStatus() = 0;
signals:
    void connectionStatusChanged();
};
#endif //TELEMETRY
// LIB_DMIF_H
