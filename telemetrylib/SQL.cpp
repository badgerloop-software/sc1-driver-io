//
// Created by Mingcan Li on 2/3/23.
//

#include "DTI.h"
#include <thread>
#include <unistd.h>

class SQL : public DTI {
public:
    SQL(QString tableToCreate) {
        this->tableToCreate = tableToCreate;

        restclient = new QNetworkAccessManager();

        t = new std::thread(&SQL::checkConnection, this);
        t->detach();
    }

    ~SQL() {
        finish = true;
        t->join();
    }

    void sendData(QByteArray bytes) override {
        auto curr_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        QUrl myurl;
        myurl.setScheme("http");
        myurl.setHost("host"); // TODO
        myurl.setPort(3000); // TODO
        myurl.setPath("/add-data"); // TODO
        myurl.setQuery("table-name=" + tableName + "&dataset-time=" + QString::fromStdString(std::to_string(curr_msec)));

        //QNetworkRequest request;
        request.setUrl(myurl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer")); // TODO Try "blob" for content type as well
        request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
        this->restclient->post(request, bytes);
    }

    std::string receiveData() override{
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        //QJsonObject json = QJsonDocument::fromJson(QByteArray::fromStdString("JSON Derulo")).object();

        if (json.isEmpty()) {
            qDebug() << "EMPTY JSON";
            return "nada";
        } else {
            tableName = json.take("response").toString();
            qDebug() << "HTTP response (table name): " << tableName;
            return tableName.toStdString();
            // TODO Automatically delete server responses since they aren't used after reading the table name
            this->restclient->setAutoDeleteReplies(true);
        }
    }

    bool getConnectionStatus() override{
        // Send request to create a new table when connection to server is first established
        if(tableName.isNull() && connection) {
            qDebug() << "Requested a new table: " << tableToCreate;

            QUrl myurl;
            myurl.setScheme("http");
            myurl.setHost("150.136.104.125"); // TODO
            myurl.setPort(3000); // TODO
            myurl.setPath("/add-table/" + tableToCreate);

            request.setUrl(myurl);
            reply = restclient->get(request);

            connect(reply, &QNetworkReply::readyRead, this, &SQL::readReply);
            request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer"));
            request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
        }

        return connection;
    }


public slots:
    void readReply() override{
        qDebug()<<"read reply invoked";
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
        //QJsonObject json = QJsonDocument::fromJson(QByteArray::fromStdString("JSON Derulo")).object();

        if(json.isEmpty()) {
            qDebug() << "EMPTY JSON";
        } else {
            tableName = json.take("response").toString();
            qDebug() << "HTTP response (table name): " << tableName;

            // TODO Automatically delete server responses since they aren't used after reading the table name
            this->restclient->setAutoDeleteReplies(true);
        }
    }

private:
    /**
     * creates a thread that ping a website to check connection
     */
    void checkConnection() {
        QTcpSocket sock;
        while(!finish) {
            sock.connectToHost("www.google.com", 80);
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
    QString tableToCreate;
    std::thread *t;
    std::atomic<bool> finish=false;
};
