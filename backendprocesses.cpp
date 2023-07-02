
#include "backendprocesses.h"

double speedFunc(double t)
{
    return t*t;
}

double solarFunc(double t)
{
    return t*t*t;
}

double batteryFunc(double t)
{
    return pow(2.71828,-t)*100;
}



BackendProcesses::BackendProcesses(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, backendProcessesOffsets offsets, QMutex &mutex, QObject *parent) :
    QObject(parent), bytes(bytes), names(names), types(types), backendOffsets(offsets), mutex(mutex),
    data(DataGen(&speedFunc,&solarFunc,&batteryFunc,100))
{
    //this->bytes = bytes;
    //this->names = names;
    //this->types = types;
    for (auto i: names) {
        qDebug() << QString::fromStdString(i); 
    }
    printf("\n");
    for (auto i: types) {
        qDebug() << QString::fromStdString(i); 
    }
    printf("\n");
    /*this->backendOffsets.tstamp_hr = offsets.tstamp_hr;
    this->backendOffsets.tstamp_mn = offsets.tstamp_mn;
    this->backendOffsets.tstamp_sc = offsets.tstamp_sc;
    this->backendOffsets.tstamp_ms = offsets.tstamp_ms;
    this->backendOffsets.tstamp_ms = offsets.mcu_hv_en;*/
}

void BackendProcesses::comm_status(bool s) {
    emit eng_dash_connection(s);
}

void BackendProcesses::startThread() {
    std::vector<DTI*> obj(2); //create a bunch of DTI instances and add them into this array in order of priority to be sent to telemetrylib
    long long first_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    obj[0]=new SQL(QString::fromStdString(std::to_string(first_msec))); //This sends data to the cloud server
    obj[1]=new TCP(QHostAddress::AnyIPv4, 4003); //this sends data thru TCP sockets
    this->tel = new Telemetry(obj);
    connect(this->tel, &Telemetry::eng_dash_connection, this, &BackendProcesses::comm_status); //for notifing the system connection status

    threadProcedure();
}

BackendProcesses::~BackendProcesses() {
    stop=true; //tells the thread to stop
}

void BackendProcesses::threadProcedure()
{
    if(stop) {
        return;
    }

    // TODO Half the frequency of the UART loop so that we don't reread mcu_hv_en in the byte array
    usleep(125000);//50000);

    //DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);

    mutex.lock();

    //bytes.clear(); // COMMENT THIS OUT
    //qDebug()<<"bytes: "<<bytes;
    // Get time data is received (then written to byte array right after byte array is updated/data is received)
    auto curr_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    //time_t now = time(NULL);

    uint8_t hour_time = (curr_msec/3600000 + 18) % 24;
    //uint8_t hour_time = (gmtime(&now)->tm_hour + 18) % 24;
    uint8_t min_time = (curr_msec/60000) % 60;
    //uint8_t min_time = gmtime(&now)->tm_min;
    uint8_t sec_time = (curr_msec/1000) % 60;
    //uint8_t sec_time = gmtime(&now)->tm_sec;
    uint16_t msec_time = curr_msec % 1000;

    //data.getData(bytes, names, types, sec_time%7+msec_time/1000.0); // COMMENT THIS OUT

    // Update timestamp in byte array
    bytes.remove(backendOffsets.tstamp_hr,1);
    bytes.insert(backendOffsets.tstamp_hr, hour_time & 0xFF);
    bytes.remove(backendOffsets.tstamp_mn,1);
    bytes.insert(backendOffsets.tstamp_mn, min_time & 0xFF);
    bytes.remove(backendOffsets.tstamp_sc,1);
    bytes.insert(backendOffsets.tstamp_sc, sec_time & 0xFF);
    bytes.remove(backendOffsets.tstamp_ms,2);
    bytes.insert(backendOffsets.tstamp_ms, msec_time & 0xFF);
    bytes.insert(backendOffsets.tstamp_ms, (msec_time >> 8) & 0xFF);

    // 60 lines of comments were removed here.
    tel->sendData(bytes, curr_msec); //this passes the data to the telemetrylib to be sent to the chase car

    mutex.unlock();
    emit dataReady();
}

void BackendProcesses::setMcuHvEn(bool state) {
    mutex.lock();
    bytes.remove(backendOffsets.mcu_hv_en, 1);
    bytes.insert(backendOffsets.mcu_hv_en, state);
    qDebug() << "mcu_hv_en in byte array: " << bytes.at(backendOffsets.mcu_hv_en);
    mutex.unlock();
}
