#ifndef __tca__h__
#define __tca__h__
#include "i2c.h"
#include "stdint.h"

#define TCA_CFG0_REG 0x06
#define TCA_CFG1_REG 0x07
#define TCA_OUT0_REG 0x02
#define TCA_OUT1_REG 0x03
#define TCA_IN0_REG 0x0
#define TCA_IN1_REG 0x1

#define TCA_NUM_PINS_PER_BANK 8

class Tca6416 : private I2c {
 private:
  int clear_settings();
  int set_dir(bool bank, int pin, uint8_t dir);
  uint8_t get_dir(bool bank, int pin);

 public:
  Tca6416(int bus, int addr);
  int begin(const uint8_t directions[]);
  uint8_t get_state(bool bank, int pin);
  int set_state(bool bank, int pin, uint8_t val);
};
#endif
