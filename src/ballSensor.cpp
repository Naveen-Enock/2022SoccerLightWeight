#include <ballSensor.h>

BallSensor::BallSensor()
{
    int adcpin1 = 0;
    int adcpin2 = 1;
    int adcpin3 = 2;
    int MOSI = 11;
    int MISO = 12;
    int sck = 13;

    adc1.begin(adcpin1, MOSI, MISO, sck);
    adc2.begin(adcpin2, MOSI, MISO, sck);
    adc3.begin(adcpin3, MOSI, MISO, sck);

    COS_IR = new double[24];
	SIN_IR = new double[24];
	for(int i = 0; i < 24; i ++) {
		COS_IR[i] = cos(toRadians( i * 15));
		SIN_IR[i] = sin(toRadians( i * 15));
	}
};


double *BallSensor::GetCosValues()
{
    return COS_IR;
}

double *BallSensor::GetSinValues()
{
    return SIN_IR;
}


int *BallSensor::GetValues()
{
    int *irval = new int[24];

    for (int i = 0; i < 24; i++)
    {
        int sensorPort = sensorOrder[i] - 1;
        int adcNumber = (sensorPort / 8) + 1;
        int channel = sensorPort % 8;
        int val = 0;
        switch (adcNumber)
        {
        case 1:
            val = adc1.analogRead(channel);
            break;
        case 2:
            val = adc2.analogRead(channel);
            break;
        case 3:
            val = adc3.analogRead(channel);
            break;

        default:
            break;
        }
        
        irval[i] = val;
    }

    return irval;
}