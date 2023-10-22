//
// Created by Mingcan Li on 2/3/23.
// Commented by ChatGPT
//
#include "Telemetry.h"

// Default constructor
Telemetry::Telemetry() {}

// Constructor with commChannels initialization
Telemetry::Telemetry(std::vector<DTI *> commChannels) {
    // Loop through all communication channels and add them to the comm vector
    for (int i = 0; i < commChannels.size(); i++) {
        this->comm.push_back(commChannels[i]);
        // Connect the signal for connection status changes to the comChannelChanged() slot
        connect(comm[i], SIGNAL(connectionStatusChanged()), this, SLOT(comChannelChanged()));
        bool status = comm[i]->getConnectionStatus();
        qDebug() << i << " :" << status << "\n";
        // If the communication channel is connected, set it as the current communication channel
        if (status && commChannel==-1) {
            commChannel = i;
            // Emit a signal indicating that the engineering dashboard is connected
            emit eng_dash_connection(true);
            // Set the current communication channel for the resend queue
            resendQueue.setChannel(comm[i]);
            // Set the communication status of the resend queue to true
            resendQueue.comStatus(true);
        }
    }
    // Output the number of initialized communication channels to console
    qDebug() << "comm channels initialized: " << comm.size();
}

// Send data through the current communication channel
void Telemetry::sendData(QByteArray bytes, long long timestamp) {
    for(int i = 0 ; i < comm.size() ; i ++) {
        comm[i]->sendData(bytes, timestamp);
    }
}

/*not doing this for now
// Receive data from the current communication channel
std::string Telemetry::receiveData() {
    // Check if there is a current communication channel
    if (commChannel != -1) {
        // Receive data from the current communication channel
        return comm[commChannel]->receiveData();
    }
    // Return "nada" if there is no current communication channel
    return "nada";
}
*/
// Slot to handle communication channel changes
void Telemetry::comChannelChanged() {
    qDebug() << "comChanged!";
    qDebug() << "\n status:";
    // Loop through all communication channels
    for (int i = 0; i < comm.size(); i++) {
        // Get the connection status of the communication channel
        bool status = comm[i]->getConnectionStatus();
        qDebug() << i << " :" << status << "\n";
        // If the communication channel is connected, set it as the current communication channel
        if (status) {
            commChannel = i;
            // Emit a signal indicating that the engineering dashboard is connected
            emit eng_dash_connection(true);
            // Set the current communication channel for the resend queue
            resendQueue.setChannel(comm[i]);
            // Set the communication status of the resend queue to true
            resendQueue.comStatus(true);
            return;
        }
    }
    // If no communication channels are connected, set the current communication channel to -1
    commChannel = -1;
    // Set the communication status of the resend queue to false
    resendQueue.comStatus(false);
    // Emit a signal indicating that the engineering dashboard is disconnected
    emit eng_dash_connection(false);
}
