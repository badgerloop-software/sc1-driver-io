#include <cstdio>
#include "serial/serialib.h"
#include <string>
#include <atomic>
#include <vector>
#include <QObject>

using namespace std;

struct GPSData {
    float lat;
    float lon;
    float alt;
};

class GPS : public QObject{
    Q_OBJECT
public:
    GPS();
    ~GPS();
    bool init(string device);
    void start_loop(string nmeaDevice);
    GPSData getLoc();
public slots:
    void autoInit(); // automatically find and init gps device
private:
    string usbnmeaprobe(vector<string> devices);
    serialib serial;
    atomic<float> lat=-1000, lon=-1000, alt=-1000;
};