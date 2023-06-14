#include <cmath>
#include "ina219.h"

// register offsets
#define CONFIGURATION_REG 0x0
#define SHUNT_VOLTAGE_REG 0x1
#define BUS_VOLTAGE_REG 0x2
#define POWER_REG 0x3
#define CURRENT_REG 0x4
#define CALIBRATION_REG 0x5

#define CONFIG_REG_DEFAULT 0x399F // default value of the configuration register

#define SHUNT_VOLTAGE_UNITS 1/100000 // 10 micro volts
#define BUS_VOLTAGE_UNITS 0.004 // 4 mV

/* Reads 2 bytes from a register.
 * Note: these wrapper functions exist because this code was copied from MainIO
 *       and I was too lazy to replace all of its uses below.
 */
uint16_t INA219::read_from_reg(uint8_t reg) {
    uint8_t data[2];
    read_bytes_from_reg(reg, data, 2);
    return (data[0] << 8) + data[1]; // convert char array to uint16_t
}

/* Write 2 bytes to a register. Can only write to the configuration and calibration registers.
 */
void INA219::write_to_reg(uint8_t reg, uint16_t val) {
    write_data<uint16_t>(reg, val);
}

INA219::INA219(int bus, int addr, float r_shunt, float max_current) : I2c(bus, addr, O_RDWR) {
    this->r_shunt = r_shunt;
    this->max_current = max_current;
}

/* Checks the value of the configuration register, sets the calibration register (required to read from power
 * and current registers), 
 * Returns 0 on success, 1 if an error occurred
 */
int INA219::begin() {
    // check value of configuration register to make sure this is the right device.
    if (read_from_reg(CONFIGURATION_REG) != CONFIG_REG_DEFAULT) {
        printf("Error reading from configuration register.\n");
        return 1;
    }

    // set calibration register value
    this->current_lsb = max_current / pow(2, 15);
    this->power_lsb = 20 * current_lsb;
    uint16_t cal = (int) (0.04096 / (current_lsb * r_shunt));
    write_to_reg(CALIBRATION_REG, cal);

    return 0;
}

/* Returns the shunt voltage in volts. 
 * The shunt voltage range is between -0.32V and +0.32V
 */
float INA219::get_shunt_voltage() {
    int16_t shunt_voltage = read_from_reg(SHUNT_VOLTAGE_REG);
    return (float)shunt_voltage * SHUNT_VOLTAGE_UNITS; // the value in the register is in units of 10 micro volts
}

/* Returns the bus voltage in volts.
 * The bus voltage range is between 0V and 32V
 */
float INA219::get_bus_voltage() {
    uint16_t bus_voltage = read_from_reg(BUS_VOLTAGE_REG) >> 3; 
    return (float)bus_voltage * BUS_VOLTAGE_UNITS; // value in register is in units of 4 mV
}

/* Returns power in watts.
 * If the value in the power register is meaningless, an error message is printed out. The function
 * still returns the power value, however. 
 */
float INA219::get_power() {
    uint16_t register_value = read_from_reg(POWER_REG);
    float power = register_value * power_lsb;
    if (check_overflow_flag()) {
        printf("power value: %f might be invalid\n", power);
    }
    return power;
}

/* Returns current in amps.
 * If the value in the current register is meaningless, an error message is printed out. The function
 * still returns the current value, however. 
 */
float INA219::get_current() {
    int16_t register_value = read_from_reg(CURRENT_REG);
    float current = register_value * current_lsb;
    if (check_overflow_flag()) {
        printf("current value: %f might be invalid\n", current);
    }
    return current;
}

/* Returns the value of the overflow flag.
 * The overflow flag is 1 when power and current calculations are out of range 
 * (data in current and power registers are meaningless)
 */
bool INA219::check_overflow_flag() {
    uint16_t bus_voltage = read_from_reg(BUS_VOLTAGE_REG);
    return (bool) (bus_voltage & 0x1); // bit 0 of the bus voltage is the overflow flag
}