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
    


if(goalOrientation <= 10 && goalOrientation >=-10)
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
    if(goalOrientation > 95 && goalOrientation < 265){
        goalAngle = initialOrientation;
    }
    Serial.print("goal Angle : ");
    Serial.println(goalAngle);
    

    
}
}

void Goal::Kick(double goalDist, bool capture, double correction)
{
    if(capture == true){
        newCap = true;
    }
    if (newCap == true && kickTimer == 0 )
    {
        if (kickWait == 10 )
        {
      

            kickActivate = 0;

            kickTimer = kickTimer + 1;
        
        }
        else if(kickWait >= 0 && kickWait <10)
        {
            kickWait += 1;
        }
        else if(kickWait >10)
        {
            kickWait = 0;
        }
        Serial.print("kick: ");
        Serial.println(kickWait);
    }

    else if (kickTimer > 0 && kickTimer <= 30)
    {
         kickTimer = kickTimer + 1;
    }
    else if(kickTimer>30 && kickTimer <= 500)
    {
        kickActivate = 1;
        kickTimer = kickTimer + 1;
        kickWait = 31;
        newCap = false;
    }

    else if (kickTimer > 500)
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
        
    }
    else if(kickActivate == 1)
    {
        digitalWrite(10, LOW);
    }
    Serial.print("kickTimer : ");
    Serial.println(kickTimer);
}