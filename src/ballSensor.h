#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <math.h>
#include <trig.h>

class BallSensor {
	public:
        BallSensor();
        int *GetValues();
        double *GetCosValues();
        double * GetSinValues();
    private:
        MCP3008 adc1;
        MCP3008 adc2;
        MCP3008 adc3;
        int sensorOrder[24] = {3,2,1,16,15,14,13,12,11,10,9,24,23,22,21,20,19,18,17,8,7,6,5,4};
        double* COS_IR;
        double* SIN_IR;

};