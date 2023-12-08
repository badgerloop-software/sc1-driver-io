#include "datafetcher.h"

DataFetcher::DataFetcher(QByteArray &bytes, int byteSize, QMutex &mutex, QObject *parent) :
    QObject(parent), bytes(bytes), byteSize(byteSize), mutex(mutex) {}

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

    // setup server
    ethServer = new QTcpServer;
    QHostAddress addr(QHostAddress::AnyIPv4);
    ethServer->listen(addr, 8000);
    connect(ethServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void DataFetcher::onNewConnection() {
    while (ethServer->hasPendingConnections()) {
        clientSocket = ethServer->nextPendingConnection();
        clientSocket->write("Connection received");
        connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(clientSocket, SIGNAL(disconnected()), SLOT(onDisconnected()));
    }
}

void DataFetcher::onReadyRead() {
    QByteArray buffer;
    QByteArray newData;

    QString startTag = "<bsr>";
    QString endTag = "</bsr>";

    // continuously get datastream from client as QByteArray
    while (true) {
        newData = clientSocket->readAll();

        while (newData.isEmpty() || !newData.contains(startTag.toUtf8())) {
            clientSocket->waitForReadyRead(1000);
            newData = clientSocket->readAll();
        }

        int startTagIndex = newData.indexOf(startTag.toUtf8());
        newData.remove(startTagIndex, startTag.size());

        while (!newData.contains(endTag.toUtf8())) {
            buffer.append(newData);
            newData = clientSocket->readAll();
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

void DataFetcher::onDisconnected() {
    clientSocket->deleteLater();
}
