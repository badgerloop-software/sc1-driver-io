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

    void sendData(QByteArray bytes, long long timestamp) override {
        //qDebug()<<"sending Via SQL: "<<timestamp;

        QUrl myurl;
        myurl.setScheme("http");
        myurl.setHost("150.136.104.125");
        myurl.setPort(3000);
        myurl.setPath("/add-data");
        myurl.setQuery("table-name=" + tableName + "&dataset-time=" + QString::fromStdString(std::to_string(timestamp)));
        //QNetworkRequest request;
        request.setUrl(myurl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer"));
        request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
        this->restclient->post(request, bytes);
    }

    /*
     std::string receiveData() override{
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();
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
    */

    bool getConnectionStatus() override{
        // Send request to create a new table when connection to server is first established
        if(tableName.isNull() && connection) {
            qDebug() << "Requested a new table: " << tableToCreate;

            QUrl myurl;
            myurl.setScheme("http");
            myurl.setHost("150.136.104.125"); 
            myurl.setPort(3000);
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
    /**
     * Read response from the server. Specifically, reads the response to the request to
     * add a new table on the server and sets tableName to the response.
     */
    void readReply() override {
        qDebug()<<"read reply invoked";
        QJsonObject json = QJsonDocument::fromJson(reply->readAll()).object();

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
            sock.connectToHost("www.google.com", 80);   //create a socket to connect google
            bool connected = sock.waitForConnected(500);    //if connected in 500ms then we say it's connected
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

    std::atomic<bool> connection = false; //connection status to the internet
    QNetworkRequest request;
    QNetworkAccessManager *restclient = NULL;
    QNetworkReply *reply;
    QString tableName; // James added this
    QString tableToCreate; 
    std::thread *t; // thread to check connection by pinging a website in the background
    std::atomic<bool> finish=false; //for soft quiting the thread
};
