#include "back2frontlink.h"

double speedFunc(double t){
    return t*t;
}

double solarFunc(double t){
    return t*t*t;
}

double batteryFunc(double t){
    return pow(2.71828,-t);
}


Back2FrontLink::Back2FrontLink(QObject *parent) : QObject(parent) {
    std::vector<unsigned char> data;
    gen=new DataGen(&speedFunc, &solarFunc, &batteryFunc, 100);
    gen->getData(data,5);
    //unpacker=new DataUnpacker(data);
}
