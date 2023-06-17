//
// Created by Mingcan Li on 1/22/23.
// Commented by ChatGPT
//
#include "DTI.h"


class TCP : public DTI {
public:
    void sendData(QByteArray bytes, long long timestamp) override {
        qDebug()<<"sending via TCP";
        bytes.push_front("<bl>");
        bytes.push_back("</bl>");
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
        return connection;
    }

    TCP(const QHostAddress& addr, int port) {
        connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
        _server.listen(addr, port);

        t = new std::thread(&TCP::checkConnection, this);
        t->detach();
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
        connection = true;
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
            connection = false;
            emit connectionStatusChanged();
        }
    }
private:
    QTcpServer _server;
    QList<QTcpSocket*> _sockets;
    std::atomic<bool> connection = false;
    std::thread *t;
    std::atomic<bool> isConnected=false;

    /**
     * creates a thread that pings the Chase car's static IP to check connection
     */
    void checkConnection() {
        QTcpSocket sock;
        while(!isConnected) {
            sock.connectToHost("196.186.1.16", 22);
            bool connected = sock.waitForConnected(500);
            if (!connected && connection) {
                sock.abort();
                connection = false;
                emit connectionStatusChanged();
            } else if(connected && !connection) {
                sock.close();
                connection = true;
                emit connectionStatusChanged();
            }
            usleep(50000);
            sock.abort();
        }
    }
};
//

