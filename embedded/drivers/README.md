# Badgerloop Serial Communication Drivers

## I<sup>2</sup>C

### Creating a New I<sup>2</sup>C Device

Create a new I<sup>2</sup>C device by deriving your device off of the base I2C class

```c++
class MyI2CDevice: private I2c {
    ...
}
```

### Opening the I<sup>2</sup>C Connection

I<sup>2</sup>C devices `begin` functions should contain this open wrapper.

```c++
if(!this->is_open()) {
    this->open_i2c();
}
```

Interact with the I<sup>2</sup>C bus by using these functions

```c++
int write_byte(uint8_t reg); // Write a byte to a register
int write_data(uint8_t, uint8_t val); // Write data to a register
int read_data(uint8_t *buff, int size); //Read data from a device
uint8_t read_from_reg(uint8_t reg); // Read data from a specific register
```

## AnalogPin class

This class represents a single analog pin on the Beaglebone Black.

### Getting started

To create a new analog pin object, call the constructor `AnalogPin::AnalogPin`. This constructor takes the pin's number as well as a scale factor to multiply the measured voltage by.

```c++
AnalogPin::AnalogPin(int pin, float scale)
```

Then, call the `Analog::begin` function to initialize the resources required to read from the analog pin.

Example:
```c++
AnalogPin potentiometerIn = AnalogPin(7, 1.0);
if (!potentiometerIn.begin()) {
    printf("Potentiometer in pin failed to begin!\n\r");
}
```

### Reading a pin

To read from an analog pin, call the `AnalogPin::readPin` function. This will read the raw value from the BBB ADC and convert it into a voltage. This voltage is then multiplied by the devices scale factor.

```c++
float readPin();
```

### The scale factor

Since the BBB adc has a 1.8 volt maximum threshold, the voltage output from devices that exceed this range will need to be divided down by some factor. The `scale` variable represents this factor.
