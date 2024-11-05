#include "Config.h"
#include <QFile>           
#include <QJsonDocument>   
#include <QDebug>          

// Singleton: Return the single instance of the Config class
Config& Config::getInstance() {
    static Config instance;  
    return instance;
}

Config::Config() {
    configObject = readConfigFile("../config.json");  
}

// Method to read the configuration file and return the parsed JSON object
QJsonObject Config::readConfigFile(const QString &filePath) {
    QFile file(filePath);  

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open config file:" << file.errorString();
        return QJsonObject();  
    }

    QByteArray fileData = file.readAll(); 
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData));  
    return jsonDoc.object();  
}

QJsonObject Config::getConfig() const {
    return configObject;
}
