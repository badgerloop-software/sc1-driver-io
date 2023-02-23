//
// Created by Mingcan Li on 2/23/23.
//

#include "Dataresend.h"


void Dataresend::setChannel(DTI *channel) {
    this->channel = channel;
}

void Dataresend::addToQueue(QByteArray arr) {
    qDebug() << "Queued msg: "<<q.size()+1<<"\n";
    mutex.lock();
    q.enqueue(arr);
    mutex.unlock();
}

void Dataresend::comStatus(bool state) {
    comstate = state;
    connect(this, SIGNAL(Dataresend::send), channel, SLOT(&DTI::sendData));
    if(state && !q.empty()) {
        t = new std::thread(&Dataresend::resend, this);
        t->detach();
    }
}

void Dataresend::resend() {
    busy = true;
    mutex.lock();
    qDebug()<<"sending";
    for(QByteArray& arr: q){
        qDebug()<<".";
        if (!comstate){
            break;
        }
        mutex.unlock();
        mutex.lock();
        emit(send(arr));
    }
    qDebug()<<"\n";
    mutex.unlock();
    busy = false;
}
