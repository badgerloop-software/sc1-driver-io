#include "i2c.h"

#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>

#include "i2c-dev.h"

/* Also need deconsturctor to close file descriptor */
I2c::I2c(int bus, int addr, int mode) {
  this->bus = bus;
  this->deviceAddress = addr;
  this->openMode = mode;
  this->fd = -1; /* This allows is_open() to function at init */
}

I2c::~I2c() {
  if (fd > 0) close(fd);
}

bool I2c::is_open() { return fd > 0; }

int I2c::open_i2c() {
  char filename[20];

  if (this->is_open()) return 0;

  if (!this->bus || !this->deviceAddress || !this->openMode) {
    std::cerr << "Device not inited.\n";
    return -EINVAL;
  }

  sprintf(filename, "/dev/i2c-%d", this->bus);
  this->fd = open(filename, this->openMode);
  if (this->fd < 0) {
    std::cerr << "Error - Could not open file\n";
    return -ENODEV;
  }

  if (ioctl(this->fd, I2C_SLAVE, this->deviceAddress)) {
    std::cerr << "Error Could not set I2C Address\n";
  }

  return 0;
}

int I2c::write_byte(uint8_t reg) {
  int response = i2c_smbus_write_byte(this->fd, reg);
  if (response < 0) {
    std::cerr << "I2C write byte error\n";
    return -EIO;
  }
#ifdef TEST
  usleep(500000);
#endif

  return 0;
}

int I2c::read_data(uint8_t *buff, int size) {
  if (read(this->fd, buff, size) != size) {
    std::cerr << "I2C read data error\n";
    return -EIO;
  }
#ifdef TEST
  usleep(500000);
#endif
  return 0;
}

uint8_t I2c::read_from_reg(uint8_t reg) {
  int rc;
  uint8_t buff[1];

  rc = this->write_byte(reg);
  if (rc) return 0xFF;
  rc = this->read_data(buff, 1);
  if (rc < 0) return 0xFF;
  return buff[0];
}

int I2c::read_bytes_from_reg(uint8_t reg, uint8_t *buff, int nBytes) {
  int rc;
  int i;

  rc = this->write_byte(reg);
  if (rc) return rc;
  rc = this->read_data(buff, nBytes);
  if (rc) return rc;
  return 0;
}
