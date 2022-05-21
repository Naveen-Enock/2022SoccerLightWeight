#include <Goal.h>
#include <Arduino.h>
Goal::Goal()
{
    kickTimer = 0;
    kickActivate = 1;
    kickWait = 0;
    goalInitiate = 0;
    realAngle = -1;
    goalDiff = 0;

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
    if (goalInitiate == 0)
    {
        realAngle = goalAngle;
        goalInitiate += 1;
    }
    goalDiff = abs(goalAngle - realAngle);
    if(goalDiff >180)
    {
        goalDiff = 360-goalDiff;
    }
    if (goalDiff<=10)
    {
        goalAngle = realAngle;
    }
    else if(goalDiff >10)
    {
        realAngle = goalAngle;
    }
    

    
}

void Goal::Kick(double goalDist, bool capture, double correction)
{
    if (capture == true && kickTimer >=0 && kickTimer <=200 && goalDist < 150)
    {
        if (kickWait == 150 )
        {
      

            kickActivate = 0;

            kickTimer = kickTimer + 1;
        
        }
        else if(kickWait >= 0 && kickWait <150)
        {
            kickWait += 1;
        }
        else if(kickWait >150)
        {
            kickWait = 0;
        }
        Serial.print("kick: ");
        Serial.println(kickWait);
    }

    else if (kickTimer > 200 && kickTimer <= 2200)
    {
        kickActivate = 1;
        kickTimer = kickTimer + 1;
        kickWait += 1;
    }

    else if (kickTimer > 2200)
    {
        kickTimer = 0;
    }
    else{
        kickWait = 0;
        kickTimer = 0;
    }
    if (kickActivate == 0)
    {
        digitalWrite(10, HIGH);
        kickActivate = 1;
    }
    else
    {
        digitalWrite(10, LOW);
    }
    Serial.print("kickTimer : ");
    Serial.println(kickTimer);
}