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
    // setup server
    ethServer = new QTcpServer;
    QHostAddress addr(QHostAddress::AnyIPv4);
    ethServer->listen(addr, 8000);
    connect(ethServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void DataFetcher::onNewConnection() {
    if (ethServer->hasPendingConnections()) {
        clientSocket = ethServer->nextPendingConnection();
        connected = true;
        clientSocket->write("Connection received");
        connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(clientSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    }
}

void DataFetcher::onReadyRead() {
    QByteArray buffer;
    QByteArray newData;

    QString startTag = "<bsr>";
    QString endTag = "</bsr>";

    // continuously get datastream from client as QByteArray
    while (connected) {
        newData = clientSocket->readAll();

        // if no data then wait and try again
        while (connected && (newData.isEmpty() || !newData.contains(startTag.toUtf8()))) {
            if(!clientSocket->waitForReadyRead(3000)) {
                onDisconnected();
                break;    
            }
            newData = clientSocket->readAll();
        }

        // remove starting tag of data packet
        int startTagIndex = newData.indexOf(startTag.toUtf8());
        newData.remove(startTagIndex, startTag.size());

        // keep getting data until the end tag is reached
        while (connected && !newData.contains(endTag.toUtf8())) {
            buffer.append(newData);
            if(!clientSocket->waitForReadyRead(3000)) {
                onDisconnected();
                break;    
            }
            newData = clientSocket->readAll();
        }
        newData = buffer.append(newData);
        buffer.clear();

        // remove the end tag
        int endTagIndex = newData.indexOf(endTag.toUtf8());
        newData.remove(endTagIndex, endTag.size());

        // trim the data at the end tag
        buffer = newData.right(newData.size() - endTagIndex);
        newData = newData.left(endTagIndex);

        // check if newData is a corrupted packet
        if (newData.size() != byteSize) {
            buffer.clear();
            continue;

        } else {
            mutex.lock();
            this->bytes = newData;
            mutex.unlock();

            // emit dataFetched signal to backendprocesses thread procedure
            emit dataFetched();
            QGuiApplication::processEvents();
        }
    }
}

void DataFetcher::onDisconnected() {
    connected = false;
    clientSocket->deleteLater();
}

void DataFetcher::sendData(QByteArray data) {
    if (ethServer->hasPendingConnections()) {
        clientSocket = ethServer->nextPendingConnection();
        clientSocket->write(data);
    }
}
