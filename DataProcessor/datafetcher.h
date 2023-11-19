#ifndef DATAFETCHER_H
#define DATAFETCHER_H

#include <QObject>
#include <vector>
#include <QMutex>
#include <QTcpSocket>
#include <QGuiApplication>

class DataFetcher : public QObject
{
    Q_OBJECT

public:
    explicit DataFetcher(QByteArray &bytes, std::string url, std::string port, int byteSize, QMutex &mutex, QObject *parent = nullptr);
    ~DataFetcher();
public slots:
    void threadProcedure();
    void startThread();
signals:
    void dataFetched();
private:
    QByteArray &bytes;
    std::string url;
    std::string port;
    int byteSize;
    QMutex &mutex;
    std::atomic<bool> stop = false;
};

#endif // DATAFETCHER_H
