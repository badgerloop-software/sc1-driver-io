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
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    //void onReadyRead();

    void threadProcedure();
    void startThread();

    // TODO Read reply from server (CURRENTLY UNUSED)
    void readReply();
    void comm_status(bool s);
signals:
    void dataReady();
    void eng_dash_connection(bool state);
private:
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;

    timestampOffsets tstampOffsets;

    QByteArray &bytes;

    std::vector<std::string> &names;
    std::vector<std::string> &types;

    // TODO For database/VPS testing
    QNetworkAccessManager *restclient;
    QNetworkReply *reply;
    QNetworkRequest request;
    QUrl myurl;
    int message_counter = 0;
    int prev_message_counter = 0;
    long long first_msec;
    int sec_counter = 0;

    QMutex &mutex;

    DataGen data;

    Telemetry* tel;

    //TCP tcp(QHostAddress::AnyIPv4, 4003);
    //TCP tcp1(QHostAddress::AnyIPv4, 4002);
};

#endif // BACKENDPROCESSES_H
