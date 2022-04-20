#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>

controlsWrapper::controlsWrapper() {

}

// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    // loop goes here
    while(true) {
        qDebug() << "test\n";
        sleep(5);
    }
}