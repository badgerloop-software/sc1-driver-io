//
// Created by Mingcan Li on 2/3/23.
// Commented by ChatGPT
//
#include "telemetry.h"

// Default constructor
Telemetry::Telemetry() {}

// Constructor with commChannels initialization
Telemetry::Telemetry(std::vector<DTI *> commChannels) {
    comm = commChannels;
    // Output the number of initialized communication channels to console
    qDebug() << "comm channels initialized: " << comm.size();
}

// Broadcast data to all communication channels 
void Telemetry::sendData(QByteArray bytes, long long timestamp) {
    // Loop through all communication channels
    for (int i = 0; i < comm.size(); i++) {
        // Send data to the current communication channel
        comm[i]->sendData(bytes, timestamp);
    }
}