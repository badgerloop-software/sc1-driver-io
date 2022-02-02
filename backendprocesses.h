#ifndef BACKENDPROCESSES_H
#define BACKENDPROCESSES_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <unistd.h>
#include "DataProcessor/DataGen.h"


class BackendProcesses : public QObject
{
    Q_OBJECT

public:
    explicit BackendProcesses(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent = nullptr);
    //~BackendProcesses();
public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    //void onReadyRead();

    void threadProcedure();
    void startThread();
signals:
    void dataReady();
private:
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;

    double time;

    QByteArray &bytes;
    std::vector<std::string> &names;
    std::vector<std::string> &types;
};

#endif // BACKENDPROCESSES_H
