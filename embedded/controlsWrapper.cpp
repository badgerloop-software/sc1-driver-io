#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>

controlsWrapper::controlsWrapper() {

}

void controlsWrapper::startThread() {
    // loop goes here
    while(true) {
        qDebug() << "test\n";
        sleep(5);
    }
}