
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
    this->tstampOffsets.unix  = timeDataOffsets.unix;


}

void BackendProcesses::comm_status(bool s) {
    emit eng_dash_connection(s);
}

void BackendProcesses::startThread() {
    qDebug()<<"a";
    std::vector<DTI*> obj(2); //create a bunch of DTI instances and add them into this array in order of priority to be sent to telemetrylib
    long long first_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    obj[0]=new SQL(QString::fromStdString(std::to_string(first_msec))); //This sends data to the cloud server
    obj[1]=new TCP(QHostAddress::AnyIPv4, 4003); //this sends data thru TCP sockets
    this->tel = new Telemetry(obj);
    connect(this->tel, &Telemetry::eng_dash_connection, this, &BackendProcesses::comm_status); //for notifing the system connection status
    qDebug()<<"b";
    threadProcedure();
}

BackendProcesses::~BackendProcesses() {
    stop=true; //tells the thread to stop
}

void BackendProcesses::threadProcedure()
{
    qDebug()<<"";
    if(stop) {
        return;
    }

    _sleep(0.1);//50000);

    //DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);

    mutex.lock();
    bytes.clear();

    // Get time data is received (then written to byte array right after byte array is updated/data is received)
    auto curr_msec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    //time_t now = time(NULL);

    uint64_t unix_time  = curr_msec;
    data.getData(bytes, names, types, unix_time);


    // Update timestamp in byte array

        bytes.remove(tstampOffsets.unix, 8);
   // declared unix timestamp as a 64 bit number so we pass in one byte at a time from most significant to least significant
    for(int i = 7 ; i >= 0 ; i--){
        bytes.insert(tstampOffsets.unix, (unix_time >> 8 * i) & 0xFF);
    }

    // 60 lines of comments were removed here.
    tel->sendData(bytes, unix_time); //this passes the data to the telemetrylib to be sent to the chase car
    mutex.unlock();
    emit dataReady();
}
