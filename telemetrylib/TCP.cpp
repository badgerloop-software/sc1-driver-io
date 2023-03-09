//
// Created by Mingcan Li on 1/22/23.
// Commented by ChatGPT
//
#include "DTI.h"

class TCP : public DTI {
public:
    void sendData(QByteArray bytes) override {
        qDebug()<<"sending via TCP";
        for (QTcpSocket* socket : _sockets) {
            socket->write(bytes);
        }
    }

    /*Nope
    std::string receiveData() override {
        if(_sockets.size() == 1) {
            //change the read parameter if there's trouble with reading the data
            return _sockets[0]->read(1000).data();
        }
        return "nada";
    }
    */

    bool getConnectionStatus() override {
        return connected;
    }

    TCP(const QHostAddress& addr, int port) {
        connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
        _server.listen(addr, port);
    }

    ~TCP() {
    }

    void connectSocket(QTcpSocket* clientSocket) {
        connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
    }
public slots:
    /*
     * The onNewConnection slot is triggered when a new connection is established. It accepts the connection, connects
     * the stateChanged signal of the new socket to the onSocketStateChanged slot of the TCP object, adds the socket to
     * the list of connected sockets, sets the connection status to true and emits the connectionStatusChanged signal.
     */
    void onNewConnection() override{
        QTcpSocket *clientSocket = _server.nextPendingConnection();
        connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
        _sockets.push_back(clientSocket);
        connected = true;
        emit connectionStatusChanged();
    };

    /*
     * The onSocketStateChanged slot is triggered when the state of a connected socket changes. If the state is
     * QAbstractSocket::UnconnectedState, it removes the socket from the list of connected sockets, sets the connection
     * status to false and emits the connectionStatusChanged signal.
     */
    void onSocketStateChanged(QAbstractSocket::SocketState state) override{
        if (state == QAbstractSocket::UnconnectedState)
        {
            QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
            _sockets.removeOne(sender);
            connected = false;
            emit connectionStatusChanged();
        }
    }
private:
    QTcpServer _server;     //the TCP socket
    QList<QTcpSocket*> _sockets;    //The list of TCP socket
    bool connected = false;     //This is used when getConnectionStatus() is called
};
//

