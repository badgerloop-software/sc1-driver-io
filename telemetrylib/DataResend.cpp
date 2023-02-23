//
// Created by Mingcan Li on 2/23/23.
//

#include "Dataresend.h"


void Dataresend::setChannel(DTI *channel) {
    this->channel = channel;
}

void Dataresend::addToQueue(QByteArray arr) {
    mutex.lock();
    q.enqueue(arr);
    mutex.unlock();
}

void Dataresend::comStatus(bool state) {
    comstate = state;
    if(!state && !q.empty()) {
        t = new std::thread(&Dataresend::resend, this);
        t->detach();
    }
}

void Dataresend::resend() {
    busy = true;
    mutex.lock();
    for(QByteArray& arr: q){
        if (!comstate){
            break;
        }
        mutex.unlock();
        mutex.lock();
        channel->sendData(arr);
    }
    mutex.unlock();
    busy = false;
}
