#ifndef __ADS1219_H__
#define __ADS1219_H__

#include "i2c.h"
#include <array>
#include <stdint.h>
#include <thread>

#define ADS11219_NUM_CHANNELS   0x3

template <typename T>
struct mutexVar {
 private:
  pthread_mutex_t mutex;
  T value = -1;

 public:
  /* volatile cannot be memcpy'd
   * so memcpy to a tmp var
   * then set the volatile
   */
  void setValue(T data) {
    pthread_mutex_lock(&mutex);
    value = data;
    pthread_mutex_unlock(&mutex);
  }
  /* reading a variable
   * doesn't require a
   * mutex lock and unlock
   *
   * but the value is private
   * so it can only be changed
   * via setValue, utilizing the mutex
   */
  T getValue(void) {
    T data;
    pthread_mutex_lock(&mutex);
    data = value;
    pthread_mutex_unlock(&mutex);
    return data;
  }
};

class Ads1219 : private I2c{

    private:
     std::array<mutexVar<float>, ADS11219_NUM_CHANNELS> voltages;
     std::thread ads_thread;
     bool stop_thread = false;
     void loop();
     
    public:
     Ads1219(int bus, int addr);
     ~Ads1219();
     int begin();
     float getVoltage(int chan);
    
};

#endif