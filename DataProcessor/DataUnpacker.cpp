//
// Created by Mingcan Li on 11/16/21.
//

#include "DataUnpacker.h"

double bytesToDouble(QByteArray data, int start_pos)
{
    double number;
    char* dataPtr = data.data();
    memcpy(&number, &dataPtr[start_pos], sizeof(double));
    return number;
}

float bytesToFloat(QByteArray data, int start_pos)
{
    float number;
    char* dataPtr = data.data();
    memcpy(&number, &dataPtr[start_pos], sizeof(float));
    return number;
}

template <typename E>
E bytesToGeneralData(QByteArray data, int startPos, int endPos, E typeZero)
{
    int byteNum=endPos-startPos;
    auto var = typeZero;

    for(int i = startPos ; i<=endPos ; i++) {
        var = var + (((uint8_t) data[i]) << (byteNum * 8));
        byteNum--;
    }

    return var;
}



DataUnpacker::DataUnpacker(QObject *parent) : QObject(parent)
{
    FILE* fp = fopen("/home/solarcar/firmware/uart-app/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    if(fp == 0) {
        fp = fopen("../uart-app/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
        if(fp == 0) {
            fp = fopen("../sc1-driver-io/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
        }
    }

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    int arrayOffset = 0;
    timestampOffsets tstampOff;
    int dataCount = 0;
    cell_group_voltages_begin = -1;
    cell_group_voltages_end = -1;
    controlsOffsets offsets;

    for(Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
        std::string name = itr->name.GetString();
        const Value& arr = itr->value.GetArray();

        names.push_back(name);
        qDebug() << QString::fromStdString(name);
        byteNums.push_back(arr[0].GetInt());
        types.push_back(arr[1].GetString());

        if(name == "tstamp_hr") {
            tstampOff.hr = arrayOffset;
        } else if(name == "tstamp_mn") {
            tstampOff.mn = arrayOffset;
        } else if(name == "tstamp_sc") {
            tstampOff.sc = arrayOffset;
        } else if(name == "tstamp_ms") {
            tstampOff.ms = arrayOffset;
        } else if(name == "horn_status") {
            offsets.horn_status = arrayOffset;
        } else if(name == "hazards") {
            offsets.hazards = arrayOffset;
        } else if(name == "headlights") {
            offsets.headlights = arrayOffset;
        } else if(name == "right_turn") {
            offsets.right_turn = arrayOffset;
        } else if(name == "left_blinker") {
            offsets.left_blinker = arrayOffset;
        } else if(name == "bl_turn_led_en") {
            offsets.bl_turn_led_en = arrayOffset;
        } else if(name == "br_turn_led_en") {
            offsets.br_turn_led_en = arrayOffset;
        } else if(name == "bc_brake_led_en") {
            offsets.bc_brake_led_en = arrayOffset;
        } else if(name == "bc_bps_led_en") {
            offsets.bc_bps_led_en = arrayOffset;
        } else if(name == "headlights_led_en") {
            offsets.headlights_led_en = arrayOffset;
        } else if(name == "fr_turn_led_en") {
            offsets.fr_turn_led_en = arrayOffset;
        } else if(name == "fl_turn_led_en") {
            offsets.fl_turn_led_en = arrayOffset;
        } else if(name == "driver_power_warning") {
            offsets.driver_power_warning = arrayOffset;
        } else if(name == "driver_power_critical") {
            offsets.driver_power_critical = arrayOffset;
        } else if(name == "driver_power_tc") {
            offsets.driver_power_tc = arrayOffset;
        } else if(name == "driver_power_valid") {
            offsets.driver_power_valid = arrayOffset;
        } else if(name == "driverIO_temp") {
            offsets.driverIO_temp = arrayOffset;
        } else if(name == "cabin_temp") {
            offsets.cabin_temp = arrayOffset;
        } else if(name == "driver_vbus_current") {
            offsets.driver_vbus_current = arrayOffset;
        } else if(name == "driver_5V_bus") {
            offsets.driver_5V_bus = arrayOffset;
        } else if(name == "driver_12V_bus") {
            offsets.driver_12V_bus = arrayOffset;
        } else if(name == "driver_vbus") {
            offsets.driver_vbus = arrayOffset;
        } else if(name == "mainIO_heartbeat") {
            offsets.mainIO_heartbeat = arrayOffset;
        } else if(name == "mcu_check") {
            offsets.mcu_check = arrayOffset;
        } else if(name == "pack_temp") {
            offsets.pack_temp = arrayOffset;
        } else if(name == "pack_current") {
            offsets.pack_current = arrayOffset;
        } else if(name == "pack_voltage") {
            offsets.pack_voltage = arrayOffset;
        } else if(name == "bps_fault") {
            offsets.bps_fault = arrayOffset;
        } else if(name == "imd_status") {
            offsets.imd_status = arrayOffset;
        } else if(name == "discharge_enable") {
            offsets.discharge_enable = arrayOffset;
        } else if(name == "voltage_failsafe") {
            offsets.voltage_failsafe = arrayOffset;
        } else if(name == "external_eStop") {
            offsets.voltage_external_eStop = arrayOffset;
        } else if(name.substr(0, 10) == "cell_group") {
            if(cell_group_voltages_begin == -1) {
                cell_group_voltages_begin = dataCount;
            } else {
                cell_group_voltages_end = dataCount;
            }
            cell_group_voltages.push_back(0);
        }
        qDebug() << cell_group_voltages_begin;
        arrayOffset += arr[0].GetInt();
        dataCount++;
    }

    fclose(fp);

    BackendProcesses* retriever = new BackendProcesses(bytes, names, types, tstampOff, mutex);

    retriever->moveToThread(&dataHandlingThread);

    connect(&dataHandlingThread, &QThread::started, retriever, &BackendProcesses::startThread);
    connect(this, &DataUnpacker::getData, retriever, &BackendProcesses::threadProcedure);
    connect(retriever, &BackendProcesses::dataReady, this, &DataUnpacker::unpack);
    connect(retriever, &BackendProcesses::eng_dash_connection, this, &DataUnpacker::eng_dash_connection);
    connect(&dataHandlingThread, &QThread::finished, retriever, &QObject::deleteLater);
    connect(&dataHandlingThread, &QThread::finished, &dataHandlingThread, &QThread::deleteLater);

    dataHandlingThread.start();
    
    controlsWrapper* loop = new controlsWrapper(bytes, mutex, restart_enable, offsets);
    loop->moveToThread(&controlsThread);
    connect(&controlsThread, &QThread::started, loop, &controlsWrapper::startThread);
    connect(&controlsThread, &QThread::finished, loop, &QObject::deleteLater);
    connect(&controlsThread, &QThread::finished, &controlsThread, &QThread::deleteLater);
    controlsThread.start();
}

DataUnpacker::~DataUnpacker()
{
    dataHandlingThread.quit();
    dataHandlingThread.wait();  //wait until the thread fully stops to avoid error message
    controlsThread.quit();
}

void DataUnpacker::unpack()
{
    int currByte = 0;

    mutex.lock();

    for(uint i=0; i < names.size(); i++) {
        if(types[i] == "float") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToFloat(bytes, currByte));
            } else if((i >= cell_group_voltages_begin) && (i <= cell_group_voltages_end)) {
                cell_group_voltages[i - cell_group_voltages_begin] = bytesToFloat(bytes, currByte);
            }
        } else if(types[i] == "uint8") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, (uint8_t)0));
            }
        } else if(types[i] == "uint16") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, (uint16_t)0));
            }
        } else if(types[i] == "bool") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, false));
            }
        } else if(types[i] == "char") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                // NOTE: char data is displayed as its ASCII decimal value, not the character, so QString is used instead
                this->setProperty(names[i].c_str(), QString::fromStdString(std::string(1, bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, (char)0))));
            }
        } else if(types[i] == "double") {
            // TODO: No double data yet; Implement when there is double data
        }

        currByte += byteNums[i];
    }

    mutex.unlock();

    this->restart_enable = checkRestartEnable();

    // Signal data update for front end
    emit dataChanged();
    // Signal to get new data
    emit getData();
}

void DataUnpacker::eng_dash_connection(bool state) {
    eng_dash_commfail = !state;
}

bool DataUnpacker::checkRestartEnable() {
    return (!restart_enable ? !mcu_hv_en : false) || driver_eStop || external_eStop || imd_status || door || crash || mcu_check || discharge_enable || restart_enable;
}

