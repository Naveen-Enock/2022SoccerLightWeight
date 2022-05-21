#include <ballAngle.h>

BallAngle::BallAngle()
{
    ballAngle = -1;

    robotAngle = -1;
    pinMode(14, INPUT);

    bool ballpresent = false;
}

void BallAngle::Process()
{
    ballpresent = false;
    sensorValues = ballSensor.GetValues();

    highestValue = 0;
    for (int i = 0; i < 24; i++)
    {
        sensorValues[i] = (sensorValues[i] - 1024) / -1;
        if (sensorValues[i] > highestValue)
        {
            highestValue = sensorValues[i];
        }
    }
    realhighestVal = highestValue;
    highestValue = highestValue / 1024;
    if (realhighestVal > 124)
    {
        ballpresent = true;
    }

    double *cosValues = ballSensor.GetCosValues();
    double *sinValues = ballSensor.GetSinValues();

    double totalCos = 0;
    double totalSin = 0;
    int threshold = min(550, (realhighestVal - 150));

    for (int i = 0; i < 24; i++)
    {
        if (sensorValues[i] < threshold)
        {
            sensorValues[i] = 0;
        }

        totalCos += sensorValues[i] * cosValues[i];
        totalSin += sensorValues[i] * sinValues[i];
    }

    ballAngle = toDegrees(atan2(totalCos, totalSin));
    if (ballAngle < 0)
    {

        ballAngle = ballAngle + 360;
    }

    // Serial.print("Ballangle : ");
    // Serial.println(ballAngle);
    CalculateRobotAngle();
}

void BallAngle::CalculateRobotAngle()
{

    double dampenVal = min(1, 0.02 * exp(5.5 * highestValue));

    double newballAngle = ballAngle > 180 ? (360 - ballAngle) : ballAngle;
    // Serial.print("ballangle : ");
    // Serial.println(newballAngle);
    double orbitvalue = min(90, 0.08 * exp(0.2 * newballAngle));
    // Serial.print("dampen : ");
    // Serial.println(dampenVal);
    // Serial.print("orbit : ");
    // Serial.println(orbitvalue);
    robotAngle = ballAngle + (ballAngle > 180 ? -1 : 1) * (orbitvalue * dampenVal);
    // Serial.print("robotAngle : ");
    // Serial.println(robotAngle);
}

void BallAngle::Intake()
{
    Serial.print("Intake : ");
    Serial.println(analogRead(14));
    if (analogRead(14) < 140)
    {
        capture = true;
    }

    else
    {
        capture = false;
    }
}
void BallAngle::kickButton()
{
    kickState = 1;
    digitalWrite(10, LOW);
    kickState = digitalRead(9);

    if (kickState == 0)
    {
        digitalWrite(10, HIGH);
    }
    else
    {
        digitalWrite(10, LOW);
    }
}
