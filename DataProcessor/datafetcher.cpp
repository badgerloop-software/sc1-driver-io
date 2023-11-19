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

    QTcpSocket socket(this);
    socket.connectToHost(QString::fromStdString(url), stoi(port));
    socket.waitForReadyRead(1000);

    QByteArray buffer;
    QByteArray newData;

    QString startTag = "<bl>";
    QString endTag = "</bl>";

    // continuously get datastream from server as QByteArray
    while (true) {
        newData = socket.readAll();

        while (newData.isEmpty() || !newData.contains(startTag.toUtf8())) {
            socket.waitForReadyRead(1000);
            newData = socket.readAll();
        }

        int startTagIndex = newData.indexOf(startTag.toUtf8());
        newData.remove(startTagIndex, startTag.size());

        while (!newData.contains(endTag.toUtf8())) {
            buffer.append(newData);
            newData = socket.readAll();
        }
        newData = buffer.append(newData);
        buffer.clear();

        int endTagIndex = newData.indexOf(endTag.toUtf8());
        newData.remove(endTagIndex, endTag.size());
        buffer = newData.right(newData.size() - endTagIndex);
        newData = newData.left(endTagIndex);

        // check if newData is a corrupted packet
        if (newData.size() != byteSize) {
            buffer.clear();
            continue;

        } else {
            qDebug() << "data:";
            qDebug() << newData;

            mutex.lock();
            this->bytes = newData;
            mutex.unlock();

            qDebug() << "size" << byteSize;
            qDebug() << "size" << bytes.size();

            emit dataFetched();
            QGuiApplication::processEvents();
        }
    }
}
