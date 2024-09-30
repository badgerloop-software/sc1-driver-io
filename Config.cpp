#include "Config.h"
#include <QFile>           // To open and read the file
#include <QJsonDocument>   // To handle JSON data
#include <QDebug>          // For debugging output

// Singleton: Return the single instance of the Config class
Config& Config::getInstance() {
    static Config instance;  // Create a single instance (lazy initialization)
    return instance;
}

// Constructor: Read the configuration file and store it in configObject
Config::Config() {
    configObject = readConfigFile("config.json");  // Adjust the file path if necessary
}

// Method to read the configuration file and return the parsed JSON object
QJsonObject Config::readConfigFile(const QString &filePath) {
    QFile file(filePath);  // Open the file

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open config file:" << file.errorString();
        return QJsonObject();  // Return an empty object if there's an error
    }

    QByteArray fileData = file.readAll();  // Read the file contents
    file.close();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData));  // Parse the JSON data
    return jsonDoc.object();  // Return the JSON object
}

// Public method to get the stored configuration object
QJsonObject Config::getConfig() const {
    return configObject;
}
