
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



BackendProcesses::BackendProcesses(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, timestampOffsets timeDataOffsets, QMutex &mutex, QObject *parent) :
    QObject(parent), bytes(bytes), names(names), types(types), mutex(mutex),
    data(DataGen(&speedFunc,&solarFunc,&batteryFunc,100))
{
    //this->bytes = bytes;
    //this->names = names;
    //this->types = types;
    this->tstampOffsets.hr = timeDataOffsets.hr;
    this->tstampOffsets.mn = timeDataOffsets.mn;
    this->tstampOffsets.sc = timeDataOffsets.sc;
    this->tstampOffsets.ms = timeDataOffsets.ms;
}

void BackendProcesses::comm_status(bool s) {
    emit eng_dash_connection(s);
}

void BackendProcesses::startThread() {
    std::vector<DTI*> obj(1); //create a bunch of DTI instances and add them into this array in order of priority to be sent to telemetrylib
    long long first_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    obj[0]=new SQL(QString::fromStdString(std::to_string(first_msec))); //This sends data to the cloud server
    //obj[1]=new TCP(QHostAddress::AnyIPv4, 4003); //this sends data thru TCP sockets
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

    usleep(100000);//50000);

    //DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);

    mutex.lock();

    bytes.clear();

    // Get time data is received (then written to byte array right after byte array is updated/data is received)
    auto curr_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    qDebug() << curr_msec;
    //time_t now = time(NULL);

    uint8_t hour_time = (curr_msec/3600000 + 18) % 24;
    //uint8_t hour_time = (gmtime(&now)->tm_hour + 18) % 24;
    uint8_t min_time = (curr_msec/60000) % 60;
    //uint8_t min_time = gmtime(&now)->tm_min;
    uint8_t sec_time = (curr_msec/1000) % 60;
    //uint8_t sec_time = gmtime(&now)->tm_sec;
    uint16_t msec_time = curr_msec % 1000;

    data.getData(bytes, names, types, sec_time%7+msec_time/1000.0);

    // Update timestamp in byte array
    bytes.remove(tstampOffsets.hr,1);
    bytes.insert(tstampOffsets.hr, hour_time & 0xFF);
    bytes.remove(tstampOffsets.mn,1);
    bytes.insert(tstampOffsets.mn, min_time & 0xFF);
    bytes.remove(tstampOffsets.sc,1);
    bytes.insert(tstampOffsets.sc, sec_time & 0xFF);
    bytes.remove(tstampOffsets.ms,2);
    bytes.insert(tstampOffsets.ms, msec_time & 0xFF);
    bytes.insert(tstampOffsets.ms, (msec_time >> 8) & 0xFF);

    // 60 lines of comments were removed here.
    tel->sendData(bytes); //this passes the data to the telemetrylib to be sent to the chase car
    mutex.unlock();
    emit dataReady();
}
