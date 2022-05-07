#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>
#include <embedded/devices/include/ads1219.h>
#include <embedded/devices/src/ads1219.cpp>

controlsWrapper::controlsWrapper(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, QMutex &mutex, QObject *parent) : QObject(parent), bytes(&bytes), names(names), types(types) {
    this->bytes = &bytes;
    this->names = names;
    this->types = types;
    this->mutex = &mutex;
}

void controlsWrapper::unlockMutex() {
    mutex->unlock();
}

void controlsWrapper::lockMutex() {
    mutex->lock();
}

void controlsWrapper::addFloatToArray(QByteArray *dataArr, float data) {
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&data);
    for (size_t i = 0; i < sizeof(float); ++i)
        dataArr->push_back(ptr[i]);
}

// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    // test ads1219
    // loop goes here
    uint8_t zero = 0;
    float data = 95;
    while(true) {
        qDebug() << "test\n";
        lockMutex();
        // Send Data
        for (int i = 0; i < 211; i++) {
            this->dataToByteArray(this->bytes, zero);
        }
        this->addFloatToArray(this->bytes, data);
        this->addFloatToArray(this->bytes, data);
        unlockMutex();
        usleep(200);
    }
}

