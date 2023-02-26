//
// Created by Mingcan Li on 2/23/23.
//

#include "DataResend.h"


void DataResend::setChannel(DTI *channel) {
    this->channel = channel;
}

void DataResend::addToQueue(QByteArray arr) {
    qDebug() << "Queued msg: "<<q.size()+1<<"\n";
    mutex.lock();
    q.enqueue(arr);
    mutex.unlock();
}

void DataResend::comStatus(bool state) {
    comstate = state;
    connect(this, SIGNAL(Dataresend::send), channel, SLOT(&DTI::sendData));
    if(state && !q.empty()) {
        t = new std::thread(&Dataresend::resend, this);
        t->detach();
    }
}

void DataResend::resend() {
    busy = true; //if dataresend is currently busy, telemetrylib would not send data directly thru channel, and indead send it thru this class
    mutex.lock(); //use a mutex to stop queue access during resend
    qDebug()<<"sending";
    for(QByteArray& arr: q){
        qDebug()<<".";
        if (!comstate){
            break;
        }
        mutex.unlock(); //additional data can be added during this temporary unlock
        mutex.lock();
        emit(send(arr));
    }
    qDebug()<<"\n";
    mutex.unlock(); //exit the loop data can be added
    busy = false;
}
