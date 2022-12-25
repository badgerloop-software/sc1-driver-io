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

// TODO For the database testing. Some may be unused
//#include <QtSql/QSqlDatabase>
#include <QScopedPointer>
#include <QDebug>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QJsonObject>


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
signals:
    void dataReady();
    void eng_dash_connection(bool state);
private:
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;

    timestampOffsets tstampOffsets;

    QByteArray &bytes;

    QMutex &mutex;
    std::vector<std::string> &names;
    std::vector<std::string> &types;

    // TODO For database/VPS testing
    QNetworkAccessManager *restclient;
    QNetworkReply *reply;
    QUrlQuery querystr;
    QNetworkRequest request;
    QUrl myurl;
    int wazzup_counter = 0;
    int prev_wazzup_counter = 0;
    long long first_msec;
    int sec_counter = 0;
};

#endif // BACKENDPROCESSES_H
