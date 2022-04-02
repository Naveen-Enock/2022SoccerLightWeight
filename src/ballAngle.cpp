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
    Log("lowestValue ");
    Logln(lowestValue);  

    double *cosValues = ballSensor.GetCosValues();
    double *sinValues = ballSensor.GetSinValues();


    double totalCos = 0;
    double totalSin = 0;
    for (int i = 0; i < 24; i++)
    {
        double sensorValue = sensorValues[i];
        double cosValue = cosValues[i];
        double sinValue = sinValues[i];

        totalCos += sensorValue * cosValue;
        totalSin += sensorValue * sinValue;
    }

    ballAngle = toDegrees(atan2(totalCos, totalSin)) + 180;

    
     robotAngle =  RobotAngle(ballAngle);

}

double BallAngle::RobotAngle(double ballAngle)
{
    
    double robotAngle;
    double newballAngle;
    double orbitvalue;
    double dampenVal = min(1, 0.02*exp(-6*(lowestValue-1)));



    if (ballAngle > 180)
    {
        newballAngle = ballAngle;
        newballAngle = 360 - newballAngle;
        orbitvalue = 0.02 * exp(0.2 * newballAngle);
        if (orbitvalue >90)
        {
            orbitvalue = 90;
        }
        
        robotAngle = ballAngle - (orbitvalue*dampenVal);
    }
    else
    {
        orbitvalue = 0.02 * exp(0.2 * ballAngle);
        if (orbitvalue > 90)
        {
            orbitvalue = 90;
        }
        robotAngle = ballAngle + (orbitvalue*dampenVal);
    }

    return robotAngle;
}
