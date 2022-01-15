#include "backendprocesses.h"

BackendProcesses::BackendProcesses(QObject *parent) : QObject(parent)
{
    unpacker = new DataUnpacker(data);
    unpacker->moveToThread(&dataHandlingThread);
    connect(&dataHandlingThread, &QThread::started, unpacker, &DataUnpacker::startThread);
    connect(this, &BackendProcesses::getData, unpacker, &DataUnpacker::threadProcedure);
    connect(unpacker, &DataUnpacker::dataReady, this, &BackendProcesses::handleData);
    connect(&dataHandlingThread, &QThread::finished, unpacker, &QObject::deleteLater);

    dataHandlingThread.start();
}

/*BackendProcesses::~BackendProcesses()
{
    dataHandlingThread.quit();
}*/

void BackendProcesses::handleData()
{
    // Update data fields
    // int
    speed = data.speed;
    charge = data.charge;
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
    lt = data.leftTurn;
    rt = data.rightTurn;
    // char
    state = data.state;

    // Signal data update for front end
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

    // Signal to get new data
    emit getData();
}
