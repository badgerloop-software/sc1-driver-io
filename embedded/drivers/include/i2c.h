#ifndef __i2c_h__
#define __i2c_h__
#include <stdint.h>
class I2c {
 private:
  int fd;
  int bus;
  int deviceAddress;
  int openMode;
  int write_byte(uint8_t reg);

 protected:
  I2c(int bus, int addr, int mode);
  ~I2c();
  int open_i2c();
  bool is_open();
  int write_data(uint8_t reg, uint8_t val);
  int read_data(uint8_t *buff, int size);
  uint8_t read_from_reg(uint8_t reg);
};
#endif
