//
// Created by Mingcan Li on 1/22/23.
#include "DTI.h"

class TCP : public DTI {
public:
    void sendData(const char* bytes) override {
        for (QTcpSocket* socket : _sockets) {
            socket->write(bytes);
        }
    }

    const char* receiveData(int max) override {
        if(_sockets.size() == 1) {
            return _sockets[0]->read(max).data();
        }
        return nullptr;
    }

    bool getConnectionStatus() override {
        return connected;
    }

    TCP(const QHostAddress& addr, int port) {

        connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
        _server.listen(addr, port);
    }

    ~TCP() {
    }

public slots:
    void onNewConnection() override{
        QTcpSocket *clientSocket = _server.nextPendingConnection();
        connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
        _sockets.push_back(clientSocket);
        connected = true;
        emit connectionStatusChanged();
    };

    void onSocketStatChanged(QAbstractSocket::SocketState state) override{
        if (state == QAbstractSocket::UnconnectedState)
        {
            QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
            _sockets.removeOne(sender);
            connected = false;
            emit connectionStatusChanged();
        }
    }
private:
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;
    bool connected = false;
};
//

