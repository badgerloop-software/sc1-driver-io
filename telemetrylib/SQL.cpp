//
// Created by Mingcan Li on 2/3/23.
//

#include "DTI.h"
#include <thread>
#include <unistd.h>

class SQL : public DTI {
public:
    SQL(QUrl myUrl) {
        request.setUrl(myUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer"));
        request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
        t = new std::thread(&SQL::checkConnection, this);
        t->detach();
    }

    ~SQL() {
        finish = true;
        t->join();
    }

    void sendData(QByteArray bytes) override {
        if(restclient == NULL)
            this->restclient = new QNetworkAccessManager();
        this->restclient->post(request, bytes);
    }

    const char* receiveData() override{
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        //QJsonObject json = QJsonDocument::fromJson(QByteArray::fromStdString("JSON Derulo")).object();

        if (json.isEmpty()) {
            qDebug() << "EMPTY JSON";
            return nullptr;
        } else {
            tableName = json.take("response").toString();
            qDebug() << "HTTP response (table name): " << tableName;
            return tableName.toStdString().c_str();
            // TODO Automatically delete server responses since they aren't used after reading the table name
            this->restclient->setAutoDeleteReplies(true);
        }
    }

    bool getConnectionStatus() override{
        return connection;
    }


private:
    /**
     * creates a thread that ping a website to check connection
     */
    void checkConnection() {
        QTcpSocket sock;
        for (;!finish;) {
            sock.connectToHost("www.pornhub.com", 80);
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

    std::atomic<bool> connection = false;
    QNetworkRequest request;
    QNetworkAccessManager *restclient = NULL;
    QNetworkReply *reply;
    QString tableName;
    std::thread *t;
    std::atomic<bool> finish=false;
};
