#include <lineSensor.h>

LineSensor::LineSensor()
{
lineValues =new  int[24];
int adcpin4 = 23;
int adcpin5 = 22;
int adcpin6 = 21;

   adc4.begin(adcpin4,11,12,13);
   adc5.begin(adcpin5,11,12,13);
   adc6.begin(adcpin6,11,12,13);



};

int *LineSensor::LineAngle()
{
       angleLS = new int[24];
	for(int i = 0; i < 24; i ++) {
		angleLS[i] = i*15;
        // Serial.print(i);
        // Serial.print(" Line sensor : ");
        // Serial.println(angleLS[i]);
	}
    return angleLS;
}

int *LineSensor::GetValues()
{
for (int i = 0; i < 24; i++)
    {

        int linePort = lineOrder[i]-1;
        
        int adcNumber = (linePort / 8) + 1;
        
        int channel = linePort % 8;
        
        int val = 0;
        switch (adcNumber)
        {
        case 1:
            val = adc4.analogRead(channel);
            break;
        case 2:
            val = adc5.analogRead(channel);
            break;
        case 3:
            val = adc6.analogRead(channel);
            break;

        default:
            break;
        }
        
        lineValues[i] = val;
        // Serial.print(i);
        // Serial.print(" Line sensor : ");
        // Serial.println(val);
        


    }

    return lineValues;
};