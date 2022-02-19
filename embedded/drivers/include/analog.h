#ifndef __ANALOG_H__
#define __ANALOG_H__
#include <stdint.h>

class AnalogPin {
 private:
  int fd;
  float scale_factor;
  int pin;

 public:
  AnalogPin(int pin, float scale_factor);
  ~AnalogPin();
  bool begin();
  bool isOpen();
  float readPin();
};

#endif
