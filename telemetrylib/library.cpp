#include "library.h"

#include <iostream>
#include <QTcpServer>
#include <vector>



telemetry::telemetry(char **url, char **protocol, int size) {
    std::vector<Connection> connections(size);
    for (int i = 0 ; i < size ; i ++) {
        if(strcmp(protocol[i], "tcp")==0) {
            connections[i].connection = new QTcpServer();
            connect(&connections[i].connection, SIGNAL(newConnection), &connections[i], SLOT(onStatusChange));

        }
    }
}

int telemetry::send(unsigned char *bytes) {

}
