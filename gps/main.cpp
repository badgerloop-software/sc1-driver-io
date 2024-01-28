#include <iostream>
#include <thread>
#include "gps.h"

using namespace std;

int main() {
    GPS gpsd;
    thread t(&GPS::autoInit, &gpsd);
    while(true) {
        //cout << "mainloop " << gpsd.getLoc().lat << "\n";
        sleep(1);
    }
}
