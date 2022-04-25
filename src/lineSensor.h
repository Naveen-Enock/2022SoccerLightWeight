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
        double *LineAngle();
        int *lineValues;
        double* angleLS;
       
    private:
    MCP3008 adc4;
    MCP3008 adc5;
    MCP3008 adc6;
    
    
    int lineOrder[24] = {19,20,21,22,23,24,1,12,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};


};