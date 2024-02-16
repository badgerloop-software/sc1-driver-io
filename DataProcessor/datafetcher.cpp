#include "datafetcher.h"

DataFetcher::DataFetcher(QByteArray &bytes, int byteSize, QMutex &mutex, GPSData gpsOffset, QObject *parent) :
    QObject(parent), bytes(bytes), byteSize(byteSize), mutex(mutex) {
        // initialize GPS
        gps = new GPS();
        #ifdef  __linux__
            gps->moveToThread(&gpsThread);
            connect(&gpsThread, &QThread::finished, gps, &QObject::deleteLater);
            connect(&gpsThread, &QThread::started, gps, &GPS::autoInit);
            gpsThread.start();
        #endif
        this->gpsOffset = gpsOffset;
    }

void DataFetcher::startThread() {
    threadProcedure();
}

DataFetcher::~DataFetcher() {
}

void DataFetcher::threadProcedure()
{
    // setup server
    ethServer = new QTcpServer;
    QHostAddress addr(QHostAddress::AnyIPv4);
    ethServer->listen(addr, 4005);
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

void insertFloat(QByteArray &data, float value, int offset) {
    QByteArray floatData;
    floatData.append(reinterpret_cast<const char*>(&value), sizeof(float));
    data.replace(offset, sizeof(float), floatData);
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
                return;  // Exit the function if disconnected
            }
            newData = clientSocket->readAll();
        }

        // remove starting tag of data packet
        int startTagIndex = newData.indexOf(startTag.toUtf8());
        newData.remove(0, startTagIndex + startTag.size());

        // keep getting data until the end tag is reached
        while (connected && !newData.contains(endTag.toUtf8())) {
            buffer.append(newData);
            if(!clientSocket->waitForReadyRead(3000)) {
                onDisconnected();
                return;  // Exit the function if disconnected
            }
            newData = clientSocket->readAll();
        }

        // remove the end tag
        int endTagIndex = newData.indexOf(endTag.toUtf8());
        newData.remove(endTagIndex, endTag.size());

        // append the remaining data from buffer
        newData.prepend(buffer);
        buffer.clear();

        // check if newData is a corrupted packet
        if (newData.size() != byteSize) {
            continue;
        }

        // fill gps data with the offset
        GPSData gpsData = gps->getLoc();
        // insert into byte array
        // if no gps device, pass through the generated data
        if (gps->initialized()) {
            insertFloat(newData, gpsData.lat, (int)gpsOffset.lat);
            insertFloat(newData, gpsData.lon, (int)gpsOffset.lon);
            insertFloat(newData, gpsData.alt, (int)gpsOffset.alt);
        }
        mutex.lock();
        this->bytes = newData;
        mutex.unlock();

        // emit dataFetched signal to backend processes thread procedure
        emit dataFetched();
        QCoreApplication::processEvents();
    }
}

void DataFetcher::onDisconnected() {
    connected = false;
    clientSocket->deleteLater();
}

void DataFetcher::sendData(QByteArray data) {
    if(connected)
        clientSocket->write(data);
}
