#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <math.h>
#include <trig.h>

class LineSensor {
	public:
        LineSensor();
        int *GetValues();
       
    private:
    MCP3008 adc4;
    MCP3008 adc5;
    MCP3008 adc6;
    int *lineValues;

};