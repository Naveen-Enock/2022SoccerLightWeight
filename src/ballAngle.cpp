#include <ballAngle.h>

BallAngle::BallAngle()
{

}

double BallAngle::GetAngle()
{
    int* sensorValues = ballSensor.GetValues();
    double* cosValues = ballSensor.GetCosValues();
    double* sinValues = ballSensor.GetSinValues();

    double totalCos = 0;
    double totalSin = 0;
    for (int i = 0; i < 24; i++)
    {
       double sensorValue =  sensorValues[i] ;
       double cosValue = cosValues [i];
       double sinValue = sinValues [i];

        totalCos +=  sensorValue * cosValue ;
        totalSin += sensorValue * sinValue;

    }
    
    double angle = toDegrees(atan2(totalCos, totalSin));


    return angle + 180;
}