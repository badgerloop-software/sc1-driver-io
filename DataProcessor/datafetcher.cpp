#include "datafetcher.h"

DataFetcher::DataFetcher(QByteArray &bytes, std::string url, std::string port, int byteSize, QMutex &mutex, QObject *parent) :
    QObject(parent), bytes(bytes), byteSize(byteSize), mutex(mutex)
{
    this->url = url;
    this->port = port;
}

void DataFetcher::startThread() {
    threadProcedure();
}

DataFetcher::~DataFetcher() {
    stop=true; //tells the thread to stop
}

void DataFetcher::threadProcedure()
{
    if(stop) {
        return;
    }

    while (true) {
        qDebug() << "starting fetcher...";
        // get datastream from server as QByteArray
        QTcpSocket socket(this);
        socket.connectToHost(QString::fromStdString(url), stoi(port));
        QByteArray extra;
        QByteArray newData = extra.append(socket.readAll());

        while (newData.isEmpty() || newData.size() > byteSize) {
            qDebug() << "data:";
            qDebug() << socket.readAll();
            if (newData.isEmpty()) {
                sleep(1);
                newData = extra.append(socket.readAll());
            }
            else if (newData.size() > byteSize) {
                extra = newData.right(newData.size() - byteSize);
                newData = newData.left(byteSize);
                break;
            }
        }

        qDebug() << newData;

        mutex.lock();
        this->bytes = newData;
        mutex.unlock();
        emit dataFetched();
    }
}
