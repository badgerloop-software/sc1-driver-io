#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonObject>   // For storing the parsed JSON object
#include <QString>       // For handling file paths
#include <QJsonDocument> // For reading JSON files

class Config {
public:
    // Static method to get the single instance of the class (Singleton pattern)
    static Config& getInstance();

    // Method to access the parsed configuration data
    QJsonObject getConfig() const;

private:
    QJsonObject configObject; // Stores the parsed config data

    // Private constructor to load the configuration file (Singleton pattern)
    Config();

    // Method to read the configuration file
    QJsonObject readConfigFile(const QString &filePath);
    
    // Disable copy constructor and assignment operator to ensure only one instance
    Config(const Config&) = delete;
    void operator=(const Config&) = delete;
};

#endif // CONFIG_H
