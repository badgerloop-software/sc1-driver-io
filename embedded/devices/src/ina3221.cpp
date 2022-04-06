#include "embedded/devices/include/ina3221.h"

#include <errno.h>

#include <iostream>

#define INA_DEVID 0x5449
#define INA_GET_VBUS_REG(channel) (channel * 2)
#define INA_GET_CURR_REG(channel) ((channel * 2) - 1)
#define INA_GET_WARN_REG(channel) ((channel * 2) + 6)
#define INA_GET_CRIT_REG(channel) ((channel * 2) + 5)

/* Register address offsets */
#define INA_CONFIG_REG 0x0
#define INA_DEVID_REG 0xFE
#define INA_PV_UPPER_REG 0x10
#define INA_PV_LOWER_REG 0x11

/* Tresholds */

// These are all currentyl defaults
#define INA_CH1_CRIT_LIM 0x7ff8
#define INA_CH2_CRIT_LIM 0x7ff8
#define INA_CH3_CRIT_LIM 0x7ff8

#define INA_CH1_WARN_LIM 0x7ff8
#define INA_CH2_WARN_LIM 0x7ff8
#define INA_CH3_WARN_LIM 0x7ff8

#define INA_PV_LOWER_LIM 0x2328
#define INA_PV_UPPER_LIM 0x2710

/* Register Bit offsets */
#define INA_CONFIG_RST 0x8000
#define INA_VOLTAGE_MASK 0x0FFF
#define INA_VOLTAGE_SIGN 0x8000

/* Calculations */
#define INA_BVOLTAGE_MULT .008
#define INA_SVOLTAGE_MULT .00004

/*
INA3221 constructor

Shunt resistor values should be passed in ohms. 1 shunt resistor per channel
*/
Ina3221::Ina3221(int bus, int addr, float shunt1, float shunt2, float shunt3)
    : I2c(bus, addr, O_RDWR) {
  this->shunts[0] = shunt1;
  this->shunts[1] = shunt2;
  this->shunts[2] = shunt3;
}

/*
Opens I2c communication with the INA3221, checks device ID register,
and initiates power on reset
*/
int Ina3221::begin() {
  int rc;
  uint16_t devid;

  rc = this->open_i2c();
  if (rc) return rc;

  // Read device register
  rc = read_bytes_from_reg(INA_DEVID_REG, (uint8_t *)&devid, 2);
  if (rc) return rc;

  if (devid != INA_DEVID) {
    std::cout << "Did not read correct device ID, read: " << devid << "\n";
    return -EIO;
  }

  // Initiate POR
  rc = write_data<uint16_t>(INA_CONFIG_REG, INA_CONFIG_RST);

  if (rc) return rc;

  // set thresholds
  uint16_t temp = INA_CH1_CRIT_LIM;
  rc = this->write_data<uint16_t>(INA_GET_CRIT_REG(1), temp);
  if (rc) return rc;
  temp = INA_CH2_CRIT_LIM;
  rc = this->write_data<uint16_t>(INA_GET_CRIT_REG(2), temp);
  if (rc) return rc;
  temp = INA_CH3_CRIT_LIM;
  rc = this->write_data<uint16_t>(INA_GET_CRIT_REG(3), temp);
  if (rc) return rc;

  temp = INA_CH1_WARN_LIM;
  rc = this->write_data<uint16_t>(INA_GET_WARN_REG(1), temp);
  if (rc) return rc;
  temp = INA_CH2_WARN_LIM;
  rc = this->write_data<uint16_t>(INA_GET_WARN_REG(2), temp);
  if (rc) return rc;
  temp = INA_CH3_WARN_LIM;
  rc = this->write_data<uint16_t>(INA_GET_WARN_REG(3), temp);
  if (rc) return rc;

  temp = INA_PV_LOWER_LIM;
  rc = this->write_data<uint16_t>(INA_PV_LOWER_REG, temp);
  if (rc) return rc;
  temp = INA_PV_UPPER_LIM;
  rc = this->write_data<uint16_t>(INA_PV_UPPER_REG, temp);

  return rc;
}

/*
Reads bus voltage for a specified channel. Returns volts.
*/
float Ina3221::readVoltage(int channel) {
  uint16_t voltage_from_reg;
  int reg;
  float voltage;
  int rc;

  if (channel < 1 || channel > INA_NUM_CHANNELS) {
    std::cout << "Channel out of range\n";
    return -EINVAL;
  }

  reg = INA_GET_VBUS_REG(channel);
  rc = read_bytes_from_reg(reg, (uint8_t *)&voltage_from_reg, 2);
  if (rc) return rc;

  // Get actual value from register
  voltage = (float)((voltage_from_reg >> 3) & INA_VOLTAGE_MASK);

  // Preserve signedness
  if (voltage_from_reg & INA_VOLTAGE_SIGN) voltage *= -1;

  return voltage * INA_BVOLTAGE_MULT;
}

/*
Reads current for a specific channel. Returns amps.
*/
float Ina3221::readCurrent(int channel) {
  uint16_t voltage_from_reg;
  int reg;
  float voltage;
  int rc;

  if (channel < 1 || channel > INA_NUM_CHANNELS) {
    std::cout << "Channel out of range\n";
    return -EINVAL;
  }

  reg = INA_GET_CURR_REG(channel);
  rc = read_bytes_from_reg(reg, (uint8_t *)&voltage_from_reg, 2);
  if (rc) return rc;

  // Get actual value from register
  voltage = (float)((voltage_from_reg >> 3) & INA_VOLTAGE_MASK);

  // Preserve signedness
  if (voltage_from_reg & INA_VOLTAGE_SIGN) voltage *= -1;

  // Return voltage divided by shunt resistor
  return (voltage * INA_SVOLTAGE_MULT) / this->shunts[channel - 1];
}
