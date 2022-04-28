#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>
#include <embedded/devices/include/ads1219.h>
#include <embedded/devices/src/ads1219.cpp>

controlsWrapper::controlsWrapper(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent) : QObject(parent), bytes(bytes), names(names), types(types) {
    this->bytes = bytes;
    this->names = names;
    this->types = types;
}

void controlsWrapper::addFloatToArray(QByteArray &dataArr, float data) {
    mutex.lock();
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&data);
    for (size_t i = 0; i < sizeof(float); ++i)
        dataArr.push_back(ptr[i]);
    mutex.unlock();
}

// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    // test ads1219
    Ads1219 testADS = new Ads1219(1, 0x40);
    testADS.begin();
    float returnedVolt;
    // loop goes here
    while(true) {
        qDebug() << "test\n";
        sleep(5);

        for (int i = 0; i < 4; i++) {
            returnedVolt = testADS.getVoltage(i);
            std::cout << "Channel " << i << ": " << returnedVolt << std::endl;
            addFloatToArray(bytes, returnedVolt);
        }


        //emit dataReady(); ? Unsure if needed at end of printing all data to signal read
    }
}
