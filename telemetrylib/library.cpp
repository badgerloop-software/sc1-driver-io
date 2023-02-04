#include "library.h"

Telemetry::Telemetry() {}
Telemetry::Telemetry(std::vector<DTI*> comm) {
    this->comm.insert(this->comm.end(),comm.begin(),comm.end());
    for(int i = 0 ; i < comm.size() ; i ++) {
        connect(comm[i], SIGNAL(connectionStatusChanged()), this, SLOT(comChannelChanged()));
    }
}

void Telemetry::sendData(const char *bytes) {
    qDebug() << "send data live comm channel: "<<comm.size();
    if(commChannel != -1) {
        comm[commChannel]->sendData(bytes);
    }
}

const char *Telemetry::receiveData() {
    return nullptr;
}

void Telemetry::comChannelChanged() {
    qDebug()<<"aa";
    for(int i = 0 ; i < comm.size() ; i ++) {
        if(comm[i]->getConnectionStatus()) {
            commChannel = i;
            emit eng_dash_connection(true);
            return;
        }
    }
    commChannel = -1;
    emit eng_dash_connection(false);
}

void Telemetry::helloworld() {
    std::cout<<"Helloworld"<<"\n";
}
