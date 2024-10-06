//
// Created by Mingcan Li on 2/3/23.
//

#include "DTI.h"
#include <thread>
#include "Config.h"

class SQL : public DTI {
public:
    
    SQL(QString tableToCreate) {
        this->tableToCreate = tableToCreate;

        restclient = new QNetworkAccessManager();
        // Send request to create a new table when connection to server is first established
        if(tableName.isNull()) {
            qDebug() << "Requested a new table: " << tableToCreate;

            QUrl myurl;
            myurl.setScheme("http");
            myurl.setHost(serverUrl); 
            myurl.setPath("/add-table/" + tableToCreate);

            request.setUrl(myurl);
            
            int transferTimeout = Config::getInstance().getConfig()["sql_transfer_timeout"].toInt();
            request.setTransferTimeout(transferTimeout);

            
            
            reply = restclient->get(request);

            connect(reply, &QNetworkReply::readyRead, this, &SQL::readReply);
            request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer"));
            request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
            lastRetry = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }
    }

    ~SQL() {
        finish = true;
        t->join();
    }

    void sendData(QByteArray bytes, long long timestamp) override {
        int transferTimeout = Config::getInstance().getConfig()["sql_transfer_timeout"].toInt();
        int retryInterval = Config::getInstance().getConfig()["sql_retry_interval"].toInt();
        qDebug()<<"sending Via SQL: "<<timestamp;
        long long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        if(tableName.isNull() && now - lastRetry > retryInterval) {
            qDebug() << "Retrying to add a new table: " << tableToCreate;

            QUrl myurl;
            myurl.setScheme("http");
            myurl.setHost(serverUrl); 
            myurl.setPath("/add-table/" + tableToCreate);

            request.setUrl(myurl);
            request.setTransferTimeout(transferTimeout);
            reply = restclient->get(request);

            connect(reply, &QNetworkReply::readyRead, this, &SQL::readReply);
            request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer"));
            request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
            lastRetry = now;
        } else {
            QUrl myurl;
            myurl.setScheme("http");
            myurl.setHost(serverUrl);
            myurl.setPath("/add-data");
            myurl.setQuery("table-name=" + tableName + "&dataset-time=" + QString::fromStdString(std::to_string(timestamp)));
            //QNetworkRequest request;
            request.setUrl(myurl);
            request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer"));
            request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
            request.setTransferTimeout(transferTimeout);
            bytes.push_front("<bsr>");
            bytes.push_back("</bsr>");
            this->restclient->post(request, bytes);
        }
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
    QString serverUrl = Config::getInstance().getConfig()["sql_server_url"].toString();

    long long lastRetry = 0;
    QNetworkRequest request;
    QNetworkAccessManager *restclient = NULL;
    QNetworkReply *reply;
    QString tableName; // James added this
    QString tableToCreate; 
    std::thread *t; // thread to check connection by pinging a website in the background
    std::atomic<bool> finish=false; //for soft quiting the thread
};
