#include "library.h"

Telemetry::Telemetry() {}
Telemetry::Telemetry(std::vector<DTI*> commChannels) {
    for(int i = 0 ; i < commChannels.size() ; i ++) {
        this->comm.push_back(commChannels[i]);
        connect(comm[i], SIGNAL(connectionStatusChanged()), this, SLOT(comChannelChanged()));
    }
    qDebug() << "comm channels initialized: "<<comm.size();
}

void Telemetry::sendData(QByteArray bytes) {
    qDebug() << "send data current comm channel: "<<commChannel;
    if(commChannel != -1 && !resendQueue.isBusy()) {
        comm[commChannel]->sendData(bytes);
    } else {
       resendQueue.addToQueue(bytes);
    }
}

std::string Telemetry::receiveData() {
    if (commChannel != -1) {
        return comm[commChannel]->receiveData();
    }
    return "nada";
}

void Telemetry::comChannelChanged() {
    qDebug()<<"comChanged!";
    qDebug()<<"\n status:";
    for(int i = 0 ; i < comm.size() ; i ++) {
        bool status = comm[i]->getConnectionStatus();
        qDebug()<<i<<" :"<<status<<"\n";
        if(status) {
            commChannel = i;
            emit eng_dash_connection(true);
            resendQueue.setChannel(comm[i]);
            resendQueue.comStatus(true);
            return;
        }
    }
    commChannel = -1;
    resendQueue.comStatus(false);
    emit eng_dash_connection(false);
}

void Telemetry::helloworld() {
    std::cout<<"Helloworld"<<"\n";
}
