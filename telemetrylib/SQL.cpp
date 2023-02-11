//
// Created by Mingcan Li on 2/3/23.
//

#include "DTI.h"
#include <thread>
#include <unistd.h>

class SQL : public DTI {
public:
    SQL(QUrl myUrl) {
        restclient = new QNetworkAccessManager();
        request.setUrl(myUrl);
        reply = this->restclient->get(request);

        connect(reply, &QNetworkReply::readyRead, this, &SQL::readReply);
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
        auto curr_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        QUrl myurl;
        myurl.setScheme("http");
        myurl.setHost("150.136.104.125"); // TODO
        myurl.setPort(3000); // TODO
        myurl.setPath("/add-data"); // TODO
        myurl.setQuery("table-name=" + tableName + "&dataset-time=" + QString::fromStdString(std::to_string(curr_msec)));

        QNetworkRequest request;
        request.setUrl(myurl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer")); // TODO Try "blob" for content type as well

        // TODO SPLIT THIS UP INTO TWO PARTS:
        //        X 1. table-name: ("_" + first_msec, which is equivalent to the response from the "/add-table/*" request) table name created from the start time of the session
        //        X 2. dataset-time: (curr_msec) timestamp associated with the byte array being sent to the server
        // TODO request.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("identifier; session-time=" + QString::fromStdString(std::to_string(first_msec))));


        //request.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("identifier; table-name=" + tableName + ",dataset-time=" + QString::fromStdString(std::to_string(curr_msec))));
        // TODO request.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("identifier; session-time=" + QString::fromStdString(std::to_string(first_msec)) + ",dataset-time=" + QString::fromStdString(std::to_string(curr_msec))));
        // TODO request.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("identifier; session-time=_quickTest,dataset-time=" + QString::fromStdString(std::to_string(curr_msec))));
        // TODO request.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("identifier; session-time=" + QString::fromStdString(std::to_string(curr_msec))));

        // TODO Note in case message frequency becomes an issue: Set up a message queue for HTTP requests,
        //      and send groups of byte arrays to the server at less frequent intervals (/as soon as we can send our next message)

        // TODO Remove: qDebug() << this->thread() << "\t\t" << restclient->thread() << "\t\t" << sec_counter;

        // TODO Allows HTTP pipelining so that the request doesn't wait for a response from the server before allowing a new message to be sent
        //      This should help to avoid stalling while waiting for a response from the server
        //      NOTE - The number of messages sent before a response from the first message is received might still be limited
        // TODO Send the byte array, along with the corresponding timestamp, to the server
        // TODO reply = this->restclient->post(request, bytes);
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
    std::thread *t;
    std::atomic<bool> finish=false;
};
