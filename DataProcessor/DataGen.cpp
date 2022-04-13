//
// Created by Mingcan Li on 11/11/21.
//

#include "DataGen.h"

int lastSpeed=0;
int lastT=0;
time_t errStartTime=0;
std::string errors="";

/**
 * Generates an array of test data
 * @param data The vector array to store the data, put an empty vector.
 * @param timeArg time
 */
void DataGen::getData(QByteArray &data, std::vector<std::string> &names, std::vector<std::string> &types, double timeArg) {
    // Add random data to bytes according to the type of each piece of data
    // Data displayed on the driver dash are given appropriate values
    for(uint i = 0; i < types.size(); i++) {
        if(types[i] == "float") {
            if((names[i] == "pack_voltage") || (names[i] == "pack_current")) {
                addFloatToArray(data,(float)sqrt(abs(solarFunc(timeArg)-0.5*1000*(speedFunc(timeArg)*speedFunc(timeArg)-lastSpeed*lastSpeed)/efficiency)));
            } else if((names[i] == "pack_temp") || (names[i] == "motor_temp") || (names[i] == "driverIO_temp") ||
                      (names[i] == "mainIO_temp") || (names[i] == "cabin_temp")) {
                addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/200));
            } else if(names[i] == "soc") {
                addFloatToArray(data,(float)batteryFunc(timeArg));
            } else if(names[i] == "accelerator") {
                addFloatToArray(data,std::fmod(timeArg,5)/*(float)rand()/((RAND_MAX+1u)/5)*/);
            } else {
                addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/100));
            }
        } else if(types[i] == "uint8") {
            if(names[i] == "speed") {
                dataToByteArray(data,(uint8_t)speedFunc(timeArg));
            } else {
                dataToByteArray(data,(uint8_t)fmod(rand(),200));
            }
        } else if(types[i] == "uint16") {
            dataToByteArray(data,(uint16_t)fmod(rand(),200));
        } else if(types[i] == "bool") {
            // For shutdown circuit inputs, any triggerred error will stay triggered for 3 seconds after the most recent error is triggered
            // When a new error is triggerred, the countdown will restart from 3 seconds for all currently triggered errors
            if((names[i] == "battery_eStop") || (names[i] == "driver_eStop") || (names[i] == "external_eStop") ||
               (names[i] == "imd_status") || (names[i] == "door") || (names[i] == "mcu_check")) {
                // NC/preferred true shutdown circuit inputs
                std::size_t errPos = errors.find(names[i]);
                bool error = (rand()%200+1 >= 2) && !((errStartTime > time(NULL) - 3) && (errPos != std::string::npos));
                dataToByteArray(data,error);
                if(!error && (errPos == std::string::npos)) {
                    time(&errStartTime);
                    errors += names[i];
                } else if((errPos != std::string::npos) && (errStartTime <= time(NULL) - 3)) {
                    errors.erase(errPos,names[i].length());
                }
            } else if(names[i] == "crash") {
                // NO/preferred false shutdown circuit inputs
                std::size_t errPos = errors.find(names[i]);
                bool error = (rand()%200+1 <= 2) || ((errStartTime > time(NULL) - 3) && (errPos != std::string::npos));
                dataToByteArray(data,error);
                if(error && (errPos == std::string::npos)) {
                    time(&errStartTime);
                    errors += names[i];
                } else if((errPos != std::string::npos) && (errStartTime <= time(NULL) - 3)) {
                    errors.erase(errPos,names[i].length());
                }
            } else {
                // Not a shutdown circuit input
                dataToByteArray(data,rand()>rand());
            }
        } else if(types[i] == "char") {
            if(names[i] == "state") {
                switch((int)fmod(rand(),4)) {
                    case 0:
                        dataToByteArray(data,'P');
                        break;
                    case 1:
                        dataToByteArray(data,'N');
                        break;
                    case 2:
                        dataToByteArray(data,'D');
                        break;
                    case 3:
                        dataToByteArray(data,'R');
                        break;
                    default:
                        dataToByteArray(data,'Q');
                        break;
                }
            } else {
                dataToByteArray(data,(char)(65+fmod(rand(),26)));
            }
        } else if(types[i] == "double") {
            addDoubleToArray(data,(double)rand()/((RAND_MAX+1u)/200));
        }
    }
}





DataGen::DataGen(func speedFunc, func solarFunc, func batteryFunc, float efficiency) {
    this->speedFunc=speedFunc;
    this->solarFunc=solarFunc;
    this->efficiency=efficiency;
    this->batteryFunc=batteryFunc;
    srand(static_cast<int>(time(0)));
}

/**
 * Since double cannot use bitwise operand, this method adds a double to the array
 * @param dataArr the data put into this array
 * @param data double data
 */
void DataGen::addDoubleToArray(QByteArray &dataArr, double data) {
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&data);
    for (size_t i = 0; i < sizeof(double); ++i)
        dataArr.push_back(ptr[i]);
}

/**
 * Since float cannot use bitwise operand, this method adds a float to the array
 * @param dataArr the data put into this array
 * @param data float data
 */
void DataGen::addFloatToArray(QByteArray &dataArr, float data) {
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&data);
    for (size_t i = 0; i < sizeof(float); ++i)
        dataArr.push_back(ptr[i]);
}

/**
 * A generic function to put data into array
 * @tparam E any type of data that can use binary operand
 * @param dataArr data put into this array
 * @param data
 */
template<typename E>
void DataGen::dataToByteArray(QByteArray &dataArr, E data) {
    for (int i = sizeof(data)-1; i >= 0 ; i--) {
        dataArr.push_back(data >> (8 * i) & 0xFF);
    }
}
