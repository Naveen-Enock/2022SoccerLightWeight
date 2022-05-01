#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Cam {
	public:
        Cam();
        double CamCalc();
        double dist;
        double buff;
        double camVal;
    private:
        
        
        std::string buffer;

};