#include "backendprocesses.h"

BackendProcesses::BackendProcesses(QObject *parent) : QObject(parent)
{
    /*unpacker = new DataUnpacker(data, floatData, charData, boolData, uint8_tData, names, types); // TODO Remove data
    // TODO unpacker = new DataUnpacker(data);
    unpacker->moveToThread(&dataHandlingThread);
    connect(&dataHandlingThread, &QThread::started, unpacker, &DataUnpacker::startThread);
    connect(this, &BackendProcesses::getData, unpacker, &DataUnpacker::threadProcedure);
    connect(unpacker, &DataUnpacker::dataReady, this, &BackendProcesses::handleData);
    connect(this, &QObject::destroyed, &dataHandlingThread, &QThread::quit); // TODO
    connect(&dataHandlingThread, &QThread::finished, unpacker, &QObject::deleteLater);
    connect(&dataHandlingThread, &QThread::finished, &dataHandlingThread, &QThread::deleteLater); // TODO

    dataHandlingThread.start();*/
    DataUnpacker* unpacker = new DataUnpacker(data, floatData, charData, boolData, uint8_tData, names, types); // TODO Remove data
    // TODO unpacker = new DataUnpacker(data);
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

    /* TODO
    // int
    this->setProperty("speed", data.speed);
    // TODO writeToProperty(speed, data.speed);
    //speed = data.speed;
    this->setProperty("charge", data.charge);
    //charge = data.charge;
    flTp = data.flTp;
    frTp = data.frTp;
    rlTp = data.rlTp;
    rrTp = data.rrTp;
    // float
    solarP = data.solarPower;
    netP = data.netPower;
    motorP = data.motorPower;
    batteryT = data.batteryTemp;
    motorT = data.motorTemp;
    motorControllerT = data.motorControllerTemp;
    // bool
    bpsFault = data.bpsFault;
    eStop = data.eStop;
    cruise = data.cruiseControl;
    leftTurn = data.leftTurn;
    rightTurn = data.rightTurn;
    // char
    state = data.state;
    */

    // Signal data update for front end
    emit dataChanged();
    /* TODO
    emit speedChanged();
    emit chargeChanged();
    emit flTpChanged();
    emit frTpChanged();
    emit rlTpChanged();
    emit rrTpChanged();
    emit solarPChanged();
    emit netPChanged();
    emit motorPChanged();
    emit batteryTChanged();
    emit motorTChanged();
    emit motorControllerTChanged();
    emit stateChanged();
    */

    // Signal to get new data
    emit getData();
}
