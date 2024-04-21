//
// Created by Mingcan Li on 1/30/24.
//

#include "DTI.h"

class UDP : public DTI {
public:
    UDP(const QHostAddress& serverAddress, int serverPort) {
        //_udpSocket.bind(localAddress, localPort);
        this->serverAddresses = serverAddress;
        this->udpPort = serverPort;
        _udpSocket = new QUdpSocket();
        emit connectionStatusChanged();
    }

    ~UDP() {
        // Cleanup and closing of the UDP socket can be added here if needed.
    }

    void sendData(QByteArray bytes, long long timestamp) override {
        qDebug() << "sending via UDP";
        bytes.prepend("<bsr>");
        bytes.append("</bsr>");
        _udpSocket->writeDatagram(bytes, serverAddresses, udpPort);
    }
    
public slots:
    void onReadyRead() {
        while (_udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(_udpSocket->pendingDatagramSize());
            QHostAddress senderAddress;
            quint16 senderPort;
            _udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
            // Process the received datagram as needed
        }
    }

private:
    QUdpSocket* _udpSocket;
    QHostAddress serverAddresses;
    int udpPort;
    std::atomic<bool> connection = true;
};