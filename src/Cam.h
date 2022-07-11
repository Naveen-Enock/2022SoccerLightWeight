#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Cam {
	public:
        Cam();
        int *angleAverage;
        int *angle2Average;
        double dist;
        double buff;
        double dist2;
        double buff2;
        double camVal;
        double camAverage();
        int *distAverage;
        int *dist2Average;
        double camSend(String role);
    private:
        
        double CamCalc();
        std::string buffer;
        char read;
        int dataNum;

};