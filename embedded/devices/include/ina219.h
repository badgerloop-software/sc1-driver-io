#ifndef __INA219_H__
#define __INA219_H__

#include "embedded/drivers/include/i2c.h"

class INA219 : private I2c {
    private:
        uint16_t read_from_reg(uint8_t reg); // helper method to read from a register
        void write_to_reg(uint8_t reg, uint16_t val); // helper method to write to a register
        bool check_overflow_flag(); // checks if the values in the current or power registers are valid
        float r_shunt; // shunt resistor
        float max_current; // maximum expected current 
        float current_lsb; // units of the value in the current register
        float power_lsb; // units of the value in the power register 
    public:
        INA219(int bus, int addr, float r_shunt, float max_current);
        int begin(); // checks if the device is correct and sets the calibration register
        float get_shunt_voltage();
        float get_bus_voltage();
        float get_power();
        float get_current();
};

#endif