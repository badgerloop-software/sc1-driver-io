#include <stdio.h>
#include <stdlib.h>

class Gpio {
 private:
  bool direction;  // 1 is input(read), 0 is output(write)
  int value;
  int pinNumber;
  std::size_t pinNumberSize;

 public:
  Gpio(int pinNumber, bool direction);
  int begin();  // sets the direction
  int setValue(bool value);
  int getValue();
};
