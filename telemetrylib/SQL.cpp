//
// Created by Mingcan Li on 2/3/23.
//

#include "DTI.h"
class SQL : public DTI {
public:
    SQL(QUrl myUrl) {
        request.setUrl(myUrl);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("arraybuffer"));
        request.setAttribute(QNetworkRequest::HttpPipeliningAllowedAttribute, true);
    }

    void sendData(QByteArray bytes) override {
        this->restclient->post(request, bytes);
    }

    const char* receiveData(int max) {

    }

private:
    QNetworkRequest request;
    QNetworkAccessManager *restclient;
    QNetworkReply *reply;
};

