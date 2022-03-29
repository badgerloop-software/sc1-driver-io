#include "embedded/devices/include/ads1219.h"
#include<iostream>


#define WRITE_CONFIG_REG 0x40 // 0100 00xx
#define READ_CONFIG_REG 0x20 // 0010 00xx
#define READ_STATUS_REG 0x24 // 0010 01xx
#define RESET 0x06 // 0000 011x
#define RDATA 0x10 // 0001 xxxx
#define START_CONVERSION 0x08 // 0000 100x
#define CONVERSION_VOLTAGE 244.14e-9

Ads1219::Ads1219(int bus, int addr) : I2c(bus, addr, O_RDWR){}

void Ads1219::loop() {
    while (this->stop_thread != true) {
        // get the current channel we are on
        uint8_t configReg = this->read_from_reg(READ_CONFIG_REG); 
        uint8_t currentChannel = configReg >> 5;
        // calculate the next channel
        if(currentChannel == 6 || currentChannel == 0){
            currentChannel = 3;
        }
        else{
            currentChannel++;
        }
        int channel = currentChannel - 3; // used to access the voltages array
        // set up the next configReg 
        configReg = (configReg & 0x1F) | (currentChannel << 5);
        // switch the channel
        this->write_data<uint8_t>(WRITE_CONFIG_REG, configReg);
        // read status register until conversion is done(it has a 1 flag)
        uint8_t statusReg = 0;
        while(statusReg == 0){
            statusReg = this->read_from_reg(READ_STATUS_REG);
            statusReg = statusReg >> 7; // get the leading bit
        }
        // get the conversion result using RDATA

        int32_t conversionResult;

        this->read_bytes_from_reg(RDATA, (uint8_t *)&conversionResult, 3);
        // do math to convert it to voltage and set the mutex variable 
        this->voltages.at(channel).setValue((float)(conversionResult >> 8) * CONVERSION_VOLTAGE);
    }
}

float Ads1219::getVoltage(int chan) {
    if(chan >= 0 || chan <= 3){
        return this->voltages.at(chan).getValue();
    }
    std::cout << "Channel number not valid.\n";
    return 0;
}

int Ads1219::begin() {
    int rc;

    rc = this->open_i2c();
    if (rc) return rc;
    this->write_byte(RESET);
    this->ads_thread = std::thread(&Ads1219::loop, this);

    return 0;
}

Ads1219::~Ads1219() {
    stop_thread = true;
}
