//
// Created by Mingcan Li on 11/11/21.
//

#include "DataGen.h"

int lastSpeed=0;
int lastT=0;
time_t errStartTime=0;
std::string errors="";

double idleTime = 1;
double upTime = 3;
double downTime = upTime * 5 / 3;
double holdTime = 1;


/**
 * Generates an array of test data
 * @param data The vector array to store the data, put an empty vector.
 * @param timeArg time
 */
void DataGen::getData(QByteArray &data, std::vector<std::string> &names, std::vector<std::string> &types, double timeArg) {
    // Add random data to bytes according to the type of each piece of data
    // Data displayed on the driver dash are given appropriate values
    double tempTime = 0;
    qDebug() << "Time arg: " << timeArg;
    if(timeArg <= idleTime) {
        tempTime = 0;
    } else if(timeArg <= (idleTime + upTime)) {
        tempTime = timeArg - idleTime;
    } else if(timeArg <= idleTime + upTime + downTime) {
        tempTime = timeArg - (idleTime + upTime);
    } else {
        tempTime = 1;
    }
    qDebug() << "Temp time: " << tempTime;

    for(uint i = 0; i < types.size(); i++) {
        if(types[i] == "float") {
            if(timeArg <= idleTime) {
                addFloatToArray(data, (float)tempTime);
            } else if(timeArg <= idleTime + upTime) {
                if(names[i] == "pack_voltage") {
                    addFloatToArray(data, (float)108.0 * tempTime/upTime);
                } else if ((names[i] == "pack_current") || (names[i] == "mppt_current_out")) {
                    addFloatToArray(data, (float)7.0 * tempTime/upTime);
                    //addFloatToArray(data,(float)sqrt(abs(solarFunc(timeArg)-0.5*1000*(speedFunc(timeArg)*speedFunc(timeArg)-lastSpeed*lastSpeed)/efficiency)));
                } else if((names[i] == "pack_temp") || (names[i] == "motor_temp") || (names[i] == "driverIO_temp") || (names[i] == "mainIO_temp")) {
                    addFloatToArray(data, (float)60.0 * tempTime/upTime);
                } else if((names[i] == "string1_temp") || (names[i] == "string2_temp") || (names[i] == "string3_temp")) {
                    addFloatToArray(data, (float)50.0 * tempTime/upTime);
                } else if(names[i] == "cabin_temp") {
                    addFloatToArray(data, (float)30.0 * tempTime/upTime);
                    //addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/200));
                } else if(names[i] == "soc") {
                    addFloatToArray(data, (float)100.0 * tempTime/upTime);
                } else if(names[i] == "accelerator") {
                    addFloatToArray(data, (float)5 * tempTime/upTime);
                    //addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/5));
                }/* else if(names[i] == "speed") {
                    addFloatToArray(data, (float)(90.0 * (tempTime/upTime)));
                }*/ else {
                    addFloatToArray(data, (float)9999.999);
                }
            } else if(timeArg <= (idleTime + upTime + downTime)) {
                if(names[i] == "pack_voltage") {
                    addFloatToArray(data, (float)108.0 - (tempTime/downTime) * 19.5);
                } else if ((names[i] == "pack_current") || (names[i] == "mppt_current_out")) {
                    addFloatToArray(data, (float)7.0 - (tempTime/downTime) * 4);
                    //addFloatToArray(data,(float)sqrt(abs(solarFunc(timeArg)-0.5*1000*(speedFunc(timeArg)*speedFunc(timeArg)-lastSpeed*lastSpeed)/efficiency)));
                } else if((names[i] == "pack_temp") || (names[i] == "motor_temp") || (names[i] == "driverIO_temp") || (names[i] == "mainIO_temp")) {
                    addFloatToArray(data, (float)60.0 - (tempTime/downTime) * 30);
                } else if((names[i] == "string1_temp") || (names[i] == "string2_temp") || (names[i] == "string3_temp")) {
                    addFloatToArray(data, (float)50.0 - 15 * (tempTime/downTime));
                } else if(names[i] == "cabin_temp") {
                    addFloatToArray(data, (float)30.0 - 7 * (tempTime/downTime));
                    //addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/200));
                } else if(names[i] == "soc") {
                    addFloatToArray(data, (float)100.0);
                } else if(names[i] == "accelerator") {
                    addFloatToArray(data, (float)5 - 5 * (tempTime/downTime));
                    //addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/5));
                } /*else if(names[i] == "speed") {
                    addFloatToArray(data, (float)(90.0 - 90 * (tempTime/downTime)));
                } */else {
                    addFloatToArray(data, (float)9999.999);
                }
            } else {
                if(names[i] == "pack_voltage") {
                    addFloatToArray(data, (float)88.5);
                } else if ((names[i] == "pack_current") || (names[i] == "mppt_current_out")) {
                    addFloatToArray(data, (float)2);
                    //addFloatToArray(data,(float)sqrt(abs(solarFunc(timeArg)-0.5*1000*(speedFunc(timeArg)*speedFunc(timeArg)-lastSpeed*lastSpeed)/efficiency)));
                } else if((names[i] == "pack_temp") || (names[i] == "motor_temp") || (names[i] == "driverIO_temp") || (names[i] == "mainIO_temp")) {
                    addFloatToArray(data, (float)30.0);
                } else if((names[i] == "string1_temp") || (names[i] == "string2_temp") || (names[i] == "string3_temp")) {
                    addFloatToArray(data, (float)35);
                } else if(names[i] == "cabin_temp") {
                    addFloatToArray(data, (float)23);
                    //addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/200));
                } else if(names[i] == "soc") {
                    addFloatToArray(data, (float)100.0);
                } else if(names[i] == "accelerator") {
                    addFloatToArray(data, (float)0);
                    //addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/5));
                } /*else if(names[i] == "speed") {
                    addFloatToArray(data, (float)0);
                } */else {
                    addFloatToArray(data, (float)9999.999);
                }
            }
        } else if(types[i] == "uint8") {
            if(names[i] == "fan_speed" || names[i] == "speed") {
                if(timeArg <= idleTime) {
                    if(names[i] == "speed") {
                         dataToByteArray(data, 0);
                    } else {
                        dataToByteArray(data, 0);
                    }
                } else if(timeArg <= idleTime + upTime) {
                    if(names[i] == "speed") {
                        dataToByteArray(data, (uint8_t)(90.0 * (tempTime/upTime)));
                    } else {
                        dataToByteArray(data, uint8_t(6 * tempTime / upTime));
                    }
                } else if(timeArg <= idleTime + upTime + downTime) {
                    if(names[i] == "speed") {
                        dataToByteArray(data, (uint8_t)(90 - 90 * (tempTime/downTime)));
                    } else {
                        dataToByteArray(data, uint8_t(6 - (tempTime / downTime) * 3));
                    }
                } else {
                    if(names[i] == "speed") {
                        dataToByteArray(data, (uint8_t)0);
                    } else {
                        dataToByteArray(data, uint8_t(3));
                    }
                }
            } else {
                dataToByteArray(data,(uint8_t)99);
            }
        } else if(types[i] == "uint16") {
            dataToByteArray(data,(uint16_t)0);
            // TODO dataToByteArray(data,(uint16_t)fmod(rand(),200));
        } else if(types[i] == "bool") {
            if((names[i] == "battery_eStop") || (names[i] == "driver_eStop") || (names[i] == "external_eStop") ||
               (names[i] == "imd_status") || (names[i] == "door") || (names[i] == "mcu_check")) {
                // NC/preferred true shutdown circuit inputs
                dataToByteArray(data, true);
            } else if(names[i] == "crash") {
                dataToByteArray(data, false);
            } else if(timeArg <= idleTime + 1) {
                dataToByteArray(data, false);
            } else if(timeArg <= idleTime + upTime + downTime / 2.0) {
                dataToByteArray(data, true);
            } else if(timeArg >= idleTime + upTime + downTime / 2.0) {
                dataToByteArray(data, false);
            }
            /*// For shutdown circuit inputs, any triggerred error will stay triggered for 3 seconds after the most recent error is triggered
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
            }*/
        } else if(types[i] == "char") {
            if(timeArg <= idleTime + upTime + downTime / 2.0) {
                dataToByteArray(data,'-');
            } else if(timeArg >= idleTime + upTime + downTime / 2.0) {
                dataToByteArray(data,'P');
            }

            /*if(names[i] == "state") {
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
            }*/
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
