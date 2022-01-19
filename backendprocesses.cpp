#include "backendprocesses.h"

BackendProcesses::BackendProcesses(QObject *parent) : QObject(parent)
{
    DataUnpacker* unpacker = new DataUnpacker(data, floatData, charData, boolData, uint8_tData, names, types); // TODO Remove data

    unpacker->moveToThread(&dataHandlingThread);
    connect(&dataHandlingThread, &QThread::started, unpacker, &DataUnpacker::startThread);
    connect(this, &BackendProcesses::getData, unpacker, &DataUnpacker::threadProcedure);
    connect(unpacker, &DataUnpacker::dataReady, this, &BackendProcesses::handleData);
    connect(&dataHandlingThread, &QThread::finished, unpacker, &QObject::deleteLater);
    connect(&dataHandlingThread, &QThread::finished, &dataHandlingThread, &QThread::deleteLater); // TODO

    dataHandlingThread.start();
}

BackendProcesses::~BackendProcesses()
{
    dataHandlingThread.quit();
}

void BackendProcesses::handleData()
{
    // Update data fields

    int numFloats = 0;
    int numUint8_ts = 0;
    int numChars = 0;
    int numBools = 0;

    for(uint i=0; i < names.size(); i++) {
        // Check the type and set the appropriate property
        if(types[i] == "float") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), floatData[numFloats]);
            }
            numFloats++;
        } else if(types[i] == "uint8") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), uint8_tData[numUint8_ts]);
            }
            numUint8_ts++;
        } else if(types[i] == "bool") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), (bool) boolData[numBools]);
            }
            numBools++;
        } else if(types[i] == "char") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                // NOTE: char data is displayed as its ASCII decimal value, not the character, so QString is used instead
                this->setProperty(names[i].c_str(), QString::fromStdString(std::string(1, charData[numChars])));
            }
            numChars++;
        } else if(types[i] == "double") {
            // TODO: No double data yet; Implement when there is double data
        }
    }

    // Signal data update for front end
    emit dataChanged();
    // Signal to get new data
    emit getData();
}
