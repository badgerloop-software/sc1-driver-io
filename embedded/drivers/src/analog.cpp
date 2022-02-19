#include "analog.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <iostream>

#define NUM_ANALOG_PINS 7
#define BBB_ADC_RANGE 1.8
#define BBB_ADC_RESOLUTION 4096.0

#define PIN_FILE_PATH "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw"

/* Copies the filepath to a given pin into a specified buffer */
#define PIN_NUMBER_TO_FILEPATH(buff, pin) (sprintf(buff, PIN_FILE_PATH, pin))

AnalogPin::AnalogPin(int pin, float scale_factor) {
  this->scale_factor = scale_factor;
  this->pin = pin;
}

AnalogPin::~AnalogPin() { close(this->fd); }

bool AnalogPin::begin() {
  char filePath[49];

  if (this->pin < 0 || this->pin >= NUM_ANALOG_PINS) {
    std::cout << "Pin number not in range\n";
    return false;
  }

  if (this->scale_factor <= 0) {
    std::cout << "Scale Factor must be positive\n";
    return false;
  }

  PIN_NUMBER_TO_FILEPATH(filePath, this->pin);
  this->fd = open(filePath, O_RDONLY);
  if (!this->isOpen()) {
    std::cout << "Failed to open file\n";
    return false;
  }
  return true;
}

bool AnalogPin::isOpen() { return this->fd > 0; }

float AnalogPin::readPin() {
  char raw[4];
  float val;

  // need to read this as a char array for some reason
  read(this->fd, raw, 4);
  val = atof(raw);

  // reset the file pointer to start from the beginning on next read
  lseek(this->fd, 0, SEEK_SET);

  return (BBB_ADC_RANGE / BBB_ADC_RESOLUTION) * val * this->scale_factor;
}
