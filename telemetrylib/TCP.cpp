//
// Created by Mingcan Li on 1/22/23.
#include "DTI.h"

class TCP : public DTI {
public:
    void sendData() {

    }

    char* receiveData() {

    }

    bool getConnectionStatus() {

    }

    TCP(std::string url, int port) {
        _server.listen(QHostAddress::AnyIPv4, 4003);
        connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    }

public slots:
    void onNewConnection() {
        QTcpSocket *clientSocket = _server.nextPendingConnection();
        connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
        _sockets.push_back(clientSocket);
    };
private:
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;

};
//

