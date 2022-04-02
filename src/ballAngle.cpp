#include <ballAngle.h>

BallAngle::BallAngle()
{
    ballAngle = -1;
    
    robotAngle = -1;
}


void BallAngle::Process()
{
    sensorValues = ballSensor.GetValues();
    lowestValue = 2000;
    for (int i = 0; i < 24; i++)
    {    
        if(sensorValues[i] < lowestValue)
        {
            lowestValue = sensorValues[i];
        }
    }
    lowestValue = lowestValue/1024; 

    double *cosValues = ballSensor.GetCosValues();
    double *sinValues = ballSensor.GetSinValues();

    double totalCos = 0;
    double totalSin = 0;
    for (int i = 0; i < 24; i++)
    {
        totalCos += sensorValues[i] * cosValues[i];
        totalSin += sensorValues[i] * sinValues[i];
    }

    ballAngle = toDegrees(atan2(totalCos, totalSin)) + 180;

    CalculateRobotAngle();

}

void BallAngle::CalculateRobotAngle()
{

    double dampenVal = min(1, 0.02*exp(-6*(lowestValue-1)));

    double newballAngle = ballAngle > 180 ? (360 - ballAngle) : ballAngle;
    double orbitvalue = min(90, 0.02 * exp(0.2 * newballAngle));
    robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue*dampenVal);
}
