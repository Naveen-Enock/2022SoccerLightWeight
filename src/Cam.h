#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Cam {
	public:
        Cam();
        double CamAngle();
        double camVal;
    private:
        double buff;
        std::string buffer;

};