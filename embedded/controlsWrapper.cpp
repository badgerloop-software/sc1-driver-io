#include "embedded/controlsWrapper.h"
#include <QDebug>

controlsWrapper::controlsWrapper() {

}

void controlsWrapper::startThread() {
    // loop goes here
    while(true) {
        qDebug() << "test\n";
    }
}