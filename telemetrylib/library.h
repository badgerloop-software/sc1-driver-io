#ifndef TELEMETRYLIB_LIBRARY_H
#define TELEMETRYLIB_LIBRARY_H
#include <QtCore>
#include <QtNetwork>

/**
 * A library built for handling data telemetry that allows automatic switch between communication methods
 */

class telemetry : public QObject{
    Q_OBJECT
public:
    /**
     * Initialize the system with following parameter
     * @param url An array of url to connect to, should be in order of preference
     * @param protocol Connection protocol for each url
     * @param size
     */
    telemetry(char ** url, char ** protocol, int size);
    int send(unsigned char * bytes);
signals:
    void eng_dash_connection(bool state);
};

class Connection : public QObject{
    Q_OBJECT
public:
    QObject* connection;
    char * type{};
    bool connectionStatus;
public slots:
    void onStatusChange(QAbstractSocket::SocketState socketState){connectionStatus = 1};
};
#endif //TELEMETRYLIB_LIBRARY_H
