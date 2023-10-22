// Created by chatGPT on 10/17/2023

#include <QUdpSocket>
#include "DTI.h"

class UDP : public DTI {
public:
    UDP(const QHostAddress& localAddress, int localPort) {
        //_udpSocket.bind(localAddress, localPort);

        emit connectionStatusChanged();
    }

    ~UDP() {
        // Cleanup and closing of the UDP socket can be added here if needed.
    }

    void sendData(QByteArray bytes, long long timestamp) override {
        qDebug() << "sending via UDP";
        bytes.prepend("<bl>");
        bytes.append("</bl>");
        QHostAddress hostAddress("192.168.1.18");
        _udpSocket.writeDatagram(bytes, hostAddress, 4003);
    }

    bool getConnectionStatus() override {
        return connection;
    }

public slots:
    void onReadyRead() {
        while (_udpSocket.hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(_udpSocket.pendingDatagramSize());
            QHostAddress senderAddress;
            quint16 senderPort;
            _udpSocket.readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
            // Process the received datagram as needed
        }
    }

    void onNewConnection() override{
        emit connectionStatusChanged();
    };
private:
    QUdpSocket _udpSocket;
    QList<QHostAddress> _clientAddresses;
    int _udpPort;
    std::atomic<bool> connection = true;
};
