#include "embedded/devices/include/tca6416.h"

#include <errno.h>
#include <fcntl.h>

#include <iostream>

Tca6416::Tca6416(int bus, int addr) : I2c(bus, addr, O_RDWR) {}

int Tca6416::clear_settings() {
  /*Reset the configuration registers*/
  if (this->write_data<uint8_t>(TCA_CFG0_REG, 0xFF) ||
      this->write_data<uint8_t>(TCA_CFG1_REG, 0xFF))
    return -1;

  /*Reset the output registers*/
  if (this->write_data<uint8_t>(TCA_OUT0_REG, 0xFF) ||
      this->write_data<uint8_t>(TCA_OUT1_REG, 0xFF))
    return -1;

  return 0;
}

int Tca6416::set_dir(bool bank, int pin, uint8_t dir) {
  uint8_t current_status;
  uint8_t dirReg;
  int rc;

  /*return an error if the pin number is invalid*/
  if (pin >= TCA_NUM_PINS_PER_BANK || pin < 0) return -1;

  /*Make sure you're reading from the right register based on bank*/
  if (bank) {
    dirReg = TCA_CFG1_REG;
  } else {
    dirReg = TCA_CFG0_REG;
  }
  current_status = this->read_from_reg(dirReg);

  /*Write the value of dir to the correct pin*/
  if (dir) {
    rc = this->write_data<uint8_t>(dirReg, current_status | (1 << pin));
  } else {
    rc = this->write_data<uint8_t>(dirReg, current_status & ~(1 << pin));
  }
  return rc;
}

uint8_t Tca6416::get_dir(bool bank, int pin) {
  uint8_t current_status;
  uint8_t dirReg;

  /*Return error if pin number invalid*/
  if (pin >= TCA_NUM_PINS_PER_BANK || pin < 0) return -1;

  /*Decide which register to use based on bank*/
  if (bank) {
    dirReg = TCA_CFG1_REG;
  } else {
    dirReg = TCA_CFG0_REG;
  }
  current_status = read_from_reg(dirReg);

  /* Shift the relevant bit all the way right, then AND with 1 to clear other
   * bits*/
  return ((current_status >> pin) & 1);
}

int Tca6416::begin(const uint8_t directions[]) {
  int rc;
  if (!this->is_open()) {
    rc = this->open_i2c();
    if (rc) return rc;
  }
  rc = this->clear_settings();
  if (rc) {
    std::cerr << "error clearing settings\n";
    return rc;
  }

  // set directions for pins in the first bank
  for (int i = 0; i < TCA_NUM_PINS_PER_BANK; ++i)
    this->set_dir(0, i, directions[i]);
  // set directions for pins in the second bank
  for (int i = 0; i < TCA_NUM_PINS_PER_BANK; ++i)
    this->set_dir(1, i, directions[TCA_NUM_PINS_PER_BANK + i]);

  // Make sure each pin in bank 0 actually received the correct value
  for (int i = 0; i < TCA_NUM_PINS_PER_BANK; ++i) {
    if (this->get_dir(0, i) != directions[i]) {
      std::cerr << "Error setting direction of pin " << i << "\n";
      return -EIO;
    }
  }
  // Repeat process for bank 1
  for (int i = 0; i < TCA_NUM_PINS_PER_BANK; ++i) {
    if (this->get_dir(1, i) != directions[TCA_NUM_PINS_PER_BANK + i]) {
      std::cerr << "Error setting direction of pin " << i << "\n";
      return -EIO;
    }
  }
  return 0;
}

uint8_t Tca6416::get_state(bool bank, int pin) {
  uint8_t current_status;
  uint8_t stateReg;
  uint8_t dir;

  if (pin >= TCA_NUM_PINS_PER_BANK || pin < 0) return -EINVAL;
  dir = get_dir(bank, pin);
  // set stateReg to the correct register
  if (bank) {
    if (dir)
      stateReg = TCA_IN1_REG;
    else
      stateReg = TCA_OUT1_REG;
  } else {
    if (dir)
      stateReg = TCA_IN0_REG;
    else
      stateReg = TCA_OUT0_REG;
  }

  current_status = this->read_from_reg(stateReg);

  return ((current_status >> pin) & 1);
}

int Tca6416::set_state(bool bank, int pin, uint8_t val) {
  uint8_t current_status;
  uint8_t current_dir;
  uint8_t stateReg;
  uint8_t dirReg;
  int rc;

  if (pin >= TCA_NUM_PINS_PER_BANK || pin < 0) return -EINVAL;

  // set the correct registers based on bank
  if (bank) {
    dirReg = TCA_CFG1_REG;
    stateReg = TCA_OUT1_REG;
  } else {
    dirReg = TCA_CFG0_REG;
    stateReg = TCA_OUT0_REG;
  }

  current_dir = this->read_from_reg(dirReg);
  if ((current_dir >> pin) & 0x1) return -EINVAL;
  current_status = this->read_from_reg(stateReg);

  if (val)
    rc = this->write_data<uint8_t>(stateReg, current_status | (1 << pin));
  else
    rc = this->write_data<uint8_t>(stateReg, current_status & ~(1 << pin));

  return rc;
}
