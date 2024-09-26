#ifndef BACKENDPROCESSES_H
#define BACKENDPROCESSES_H
#ifdef unix
#undef unix
#endif

#include <QGuiApplication>
#include <QObject>
#include <vector>
#include <QMutex>
#include <fstream>

#include "telemetrylib/Telemetry.h"
#include "telemetrylib/DTI.h"
#include "telemetrylib/TCP.cpp"
#include "telemetrylib/SQL.cpp"
#include "telemetrylib/UDP.cpp"
#include "telemetrylib/Serial.cpp"

struct timestampOffsets {
    int hr;
    int mn;
    int sc;
    int ms;
    int unix;
};

class BackendProcesses : public QObject
{
    Q_OBJECT

public:
    explicit BackendProcesses(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, timestampOffsets timeDataOffsets, QMutex &mutex, int byteSize, QObject *parent = nullptr);
    ~BackendProcesses();
    //~BackendProcesses();
public slots:
    void threadProcedure();
    void startThread();
    void comm_status(bool s);
signals:
    void eng_dash_connection(bool state);
    void dataReady();
private:

    timestampOffsets tstampOffsets;

    QByteArray &bytes;

    std::atomic<bool> stop = false;
    std::vector<std::string> &names;
    std::vector<std::string> &types;

    QMutex &mutex;

    int byteSize;

    Telemetry* tel;

    // path of output directory used for file sync
    QString basePath;

    // timestamp when the last file sync output was written to disk
    uint8_t last_minute = 0;

    // queued data for file sync
    QByteArray all_bytes_in_minute;
};

#endif // BACKENDPROCESSES_H
