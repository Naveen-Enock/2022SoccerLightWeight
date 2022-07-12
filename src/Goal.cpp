#include <Goal.h>
#include <Arduino.h>
Goal::Goal()
{
    kickTimer = 0;
    kickActivate = 1;
    kickWait = 0;
    goalInitiate = 0;
    realAngle = 0;
    goalDiff = 0;

}
void Goal::Process(int Orientation, double goalOrientation, int initialOrientation)
{

   if(goalOrientation ==-5){

        goalAngle = initialOrientation;
   }
   else{
    if (goalOrientation > 180)
    {
        goalOrientation = goalOrientation - 360;
    }
    


if(goalOrientation <= 5 && goalOrientation >=-5)
{
    goalOrientation = 0;
}



    goalAngle = Orientation + goalOrientation;

    if (goalAngle > 360)
    {
        goalAngle = goalAngle - 360;
    }
    else if (goalAngle < 0)
    {
        goalAngle = goalAngle + 360;
    }
    Serial.print("goal Angle : ");
    Serial.println(goalAngle);
    

    
}
}

void Goal::Kick(double goalDist, bool capture, double correction)
{
    if (capture == true && kickTimer >=0 && kickTimer <=200 && goalDist < 500)
    {
        if (kickWait == 30 )
        {
      

            kickActivate = 0;

            kickTimer = kickTimer + 1;
        
        }
        else if(kickWait >= 0 && kickWait <30)
        {
            kickWait += 1;
        }
        else if(kickWait >30)
        {
            kickWait = 0;
        }
        Serial.print("kick: ");
        Serial.println(kickWait);
    }

    else if (kickTimer > 200 && kickTimer <= 800)
    {
        kickActivate = 1;
        kickTimer = kickTimer + 1;
        kickWait += 1;
    }

    else if (kickTimer > 800)
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