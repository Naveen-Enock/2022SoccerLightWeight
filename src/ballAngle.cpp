#include <ballAngle.h>

BallAngle::BallAngle()
{
}

double BallAngle::GetAngle()
{
    sensorValues = ballSensor.GetValues();
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

    double angle = toDegrees(atan2(totalCos, totalSin)) + 180;

    
     return RobotAngle(angle);
}

double BallAngle::RobotAngle(double ballAngle)
{
    Serial.print("BallAngle : ");
    Serial.println(ballAngle);
    double robotAngle;
    double newballAngle;
    double orbitvalue;
    int strengthNum = (90-ballAngle)/15;

    if (ballAngle > 180)
    {
        newballAngle = ballAngle;
        newballAngle = 360 - newballAngle;
        orbitvalue = 0.02 * exp(0.2 * newballAngle);
        if (orbitvalue >90)
        {
            orbitvalue = 90;
        }
        
        robotAngle = ballAngle - orbitvalue;
    }
    else
    {
        orbitvalue = 0.02 * exp(0.2 * ballAngle);
        if (orbitvalue > 90)
        {
            orbitvalue = 90;
        }
        robotAngle = ballAngle + orbitvalue;
    }

    return robotAngle;
}