
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



BackendProcesses::BackendProcesses(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, timestampOffsets timeDataOffsets, QMutex &mutex, int byteSize, QObject *parent) :
    QObject(parent), bytes(bytes), names(names), types(types), mutex(mutex)
{
    this->bytes = bytes;
    this->names = names;
    this->types = types;
    this->byteSize = byteSize;

    this->tstampOffsets.hr = timeDataOffsets.hr;
    this->tstampOffsets.mn = timeDataOffsets.mn;
    this->tstampOffsets.sc = timeDataOffsets.sc;
    this->tstampOffsets.ms = timeDataOffsets.ms;
    this->tstampOffsets.unix = timeDataOffsets.unix;

    // determine base path (should handle Unix and Win32 correctly)
    basePath = QDir::tempPath() + "/driver-io-file-sync/";
    qDebug() << basePath;
    if (!QDir(basePath).exists()) {
        QDir().mkdir(basePath);
    }
}

void BackendProcesses::comm_status(bool s) {
    emit eng_dash_connection(s);
}

void BackendProcesses::startThread() {
    std::vector<DTI*> obj(2); //create a bunch of DTI instances and add them into this array in order of priority to be sent to telemetrylib
    long long first_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    obj[0]=new SQL(QString::fromStdString(std::to_string(first_msec))); //This sends data to the cloud server
    obj[1]=new UDP(QHostAddress("127.0.0.1"), 4003); //This sends data to the chase car
    this->tel = new Telemetry(obj);
    connect(this->tel, &Telemetry::eng_dash_connection, this, &BackendProcesses::comm_status); //for notifing the system connection status
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
    bytes.remove(tstampOffsets.unix,8);
    uint64_t time=curr_msec;
    int mask= 56;
    for(int i=0; i<=7; i++) {
        bytes.insert(tstampOffsets.unix,(time>>mask) & 0xFF);
        mask=mask-8;
    }
    // write byte array to file for sync, once a minute
    static QByteArray all_bytes_in_minute = QByteArray();
    all_bytes_in_minute.push_back("<bsr>");
    all_bytes_in_minute.push_back(bytes);
    all_bytes_in_minute.push_back("</bsr>");

    // only output the file when our buffer has reached 
    if (all_bytes_in_minute.size() >= 10000 || min_time != last_minute) {
        std::ofstream(basePath.toStdString() + std::to_string(curr_msec) + "_all_bytes.bin", std::ios::binary)
            .write(all_bytes_in_minute.data(), all_bytes_in_minute.size());
        last_minute = min_time;
        all_bytes_in_minute.clear();
    }

    // 60 lines of comments were removed here.
    tel->sendData(bytes, curr_msec); //this passes the data to the telemetrylib to be sent to the chase car
    mutex.unlock();
    emit dataReady();
}
