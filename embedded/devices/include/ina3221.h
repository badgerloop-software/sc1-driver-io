#ifndef __INA3221_H__
#define __INA3221_H__

#include <stdint.h>

#include "i2c.h"

#define INA_NUM_CHANNELS 0x3

class Ina3221 : private I2c {
 private:
  float shunts[3];

 public:
  Ina3221(int bus, int addr, float shunt1, float shunt2, float shunt3);
  int begin();
  float readVoltage(int channel);
  float readCurrent(int channel);
};

#endif
