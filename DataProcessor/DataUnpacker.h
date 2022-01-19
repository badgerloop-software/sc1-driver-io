//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAPROCESSOR_DATAUNPACKER_H
#define DATAPROCESSOR_DATAUNPACKER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <unistd.h>
#include "DataGen.h"
#include "3rdparty/rapidjson/document.h"
#include "3rdparty/rapidjson/filereadstream.h"

using namespace rapidjson;

typedef unsigned char byte;

class DataUnpacker : public QObject
{
    Q_OBJECT

public:
    explicit DataUnpacker(std::vector<float> &floatData, std::vector<char> &charData, std::vector<uint8_t> &boolData, std::vector<uint8_t> &uint8_tData, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent = nullptr);
    //~DataUnpacker();
public slots:
    void onNewConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onReadyRead();

    void threadProcedure();
    void startThread();
signals:
    void dataReady();
private:
    void unpack(QByteArray rawData);

    QTcpServer _server;
    QList<QTcpSocket*> _sockets;

    double time;

    std::vector<float> &floatData;
    std::vector<char> &charData;
    std::vector<uint8_t> &boolData; // It didn't like passing a bool to bytesToSomethingNotDouble for some reason
    std::vector<uint8_t> &uint8_tData;
    std::vector<std::string> &names;
    std::vector<int> byteNums;
    std::vector<std::string> &types;
};


#endif //DATAGENERATOR_DATAUNPACKER_H
