#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include <QObject>
#include <vector>
#include <QMutex>
#include <QTcpSocket>
#include <QTcpServer>
#include <QGuiApplication>
#include <QThread>
#include "gps/gps.h"
class DataFetcher : public QObject
{
    Q_OBJECT

public:
    explicit DataFetcher(QByteArray &bytes, int byteSize, QMutex &mutex, GPSData gpsOffset, QObject *parent = nullptr);
    ~DataFetcher();
public slots:
    void threadProcedure();
    void startThread();
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
    void sendData(QByteArray data);
signals:
    void dataFetched();
private:
    QByteArray &bytes;
    int byteSize;
    QMutex &mutex;
    std::atomic<bool> connected = false;
    QThread* thread;

    GPS* gps;
    GPSData gpsOffset;
    QThread gpsThread;
    QTcpServer* ethServer;
    QTcpSocket* clientSocket;
};

#endif // DATAFETCHER_H
