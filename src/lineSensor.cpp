#include <lineSensor.h>

LineSensor::LineSensor()
{
    lineValues = new int[24];
    prevVal = new int[24];
    int adcpin4 = 23;
    int adcpin5 = 22;
    int adcpin6 = 21;
    coefficient = 0.1;

    adc4.begin(adcpin4, 11, 12, 13);
    adc5.begin(adcpin5, 11, 12, 13);
    adc6.begin(adcpin6, 11, 12, 13);

    angleLS = new int[24];
        COS_IR = new double[24];
	SIN_IR = new double[24];
    	for(int i = 0; i < 24; i ++) {
		COS_IR[i] = cos(toRadians( i * 15));
		SIN_IR[i] = sin(toRadians( i * 15));
        prevVal[i] = -1;
	}
};

int *LineSensor::LineAngle()
{
    for (int i = 0; i < 24; i++)
    {
        angleLS[i] = i * 15;

    }
    return angleLS;
}

double *LineSensor::GetCosValues()
{
    return COS_IR;
}

double *LineSensor::GetSinValues()
{
    return SIN_IR;
}

int *LineSensor::GetValues()
{
    for (int i = 0; i < 24; i++)
    {

        int linePort = lineOrder[i] - 1;

        int adcNumber = (linePort / 8) + 1;

        int channel = linePort % 8;

        int val = 0;
        switch (adcNumber)
        {
        case 1:
            digitalWrite(23,LOW);
            val = adc4.analogRead(channel);
            break;
        case 2:
        digitalWrite(22,LOW);
            val = adc5.analogRead(channel);
            break;
        case 3:
        digitalWrite(21,LOW);
            val = adc6.analogRead(channel);
            break;

        default:
            break;
        }

        lineValues[i] = val;
        if(prevVal[i] == -1){
            prevVal[i]= lineValues[i];
        } 
        lineValues[i] = (coefficient*(prevVal[i])) + ((1-coefficient)*(lineValues[i]));
        prevVal[i] = lineValues[i];
          
        //  Serial.print(i);
        //  Serial.print(" Line sensor : ");
        //  Serial.println(val);
    }

    return lineValues;
};
