#include <Goal.h>
#include <Arduino.h>
Goal::Goal()
{
    kickTimer = 0;
}
void Goal::Process(int initialOrientation, double goalOrientation)
{
    if (goalOrientation > 180)
    {
        goalOrientation = goalOrientation - 360;
    }

    goalAngle = initialOrientation + goalOrientation;
    if (goalAngle > 360)
    {
        goalAngle = goalAngle - 360;
    }
    else if (goalAngle < 0)
    {
        goalAngle = goalAngle + 360;
    }
}

void Goal::Kick(double goalDist)
{
    if (goalDist < 70)
    {

        if (kickTimer == 0)
        {
            digitalWrite(10, HIGH);
            kickTimer = kickTimer + 1;
        }
        
    }
    if (kickTimer > 0 && kickTimer <= 5000)
        {
            kickTimer = kickTimer + 1;
        }
    else if (kickTimer > 5000)
        {
            kickTimer = 0;
        }
}