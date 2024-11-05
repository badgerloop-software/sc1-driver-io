#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonObject>  
#include <QString>      
#include <QJsonDocument> 

class Config {
public:
    
    static Config& getInstance();
    QJsonObject getConfig() const;

private:
    QJsonObject configObject;

    Config();

    QJsonObject readConfigFile(const QString &filePath);
    
    Config(const Config&) = delete;
    void operator=(const Config&) = delete;
};

#endif // CONFIG_H
