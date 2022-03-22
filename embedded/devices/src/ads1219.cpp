#include "ads1219.h"


Ads1219::Ads1219(int bus, int addr) : I2c(bus, addr, O_RDWR){}

void Ads1219::loop() {
    while (this->stop_thread != true) {

    }
}

float getVoltage(int chan) {
    
}

int Ads1219::begin() {
    int rc;

    rc = this->open_i2c();
    if (rc) return rc;

    ads_thread = std::thread(loop);

    return 0;
}

Ads1219::~Ads1219() {
    stop_thread = true;
}
