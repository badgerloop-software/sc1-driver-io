#ifndef BACKENDPROCESSES_H
#define BACKENDPROCESSES_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <QMutex>
#include "DataProcessor/DataGen.h"

// TODO For database testing
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "telemetrylib/library.h"
#include "telemetrylib/DTI.h"
#include "telemetrylib/TCP.cpp"
#include "telemetrylib/SQL.cpp"

struct timestampOffsets {
    int hr;
    int mn;
    int sc;
    int ms;
};

class BackendProcesses : public QObject
{
    Q_OBJECT

public:
    explicit BackendProcesses(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, timestampOffsets timeDataOffsets, QMutex &mutex, QObject *parent = nullptr);
    //~BackendProcesses();
public slots:
    void threadProcedure();
    void startThread();

    // TODO Read reply from server (CURRENTLY UNUSED)
    void comm_status(bool s);
signals:
    void dataReady();
    void eng_dash_connection(bool state);
private:

    timestampOffsets tstampOffsets;

    QByteArray &bytes;

    std::vector<std::string> &names;
    std::vector<std::string> &types;

    QMutex &mutex;

    DataGen data;

    Telemetry* tel;
};

#endif // BACKENDPROCESSES_H
