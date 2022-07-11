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
    
// if(goalOrientation < -10)
// {
//     goalOrientation = -50;
// }
// else if(goalOrientation > 10)
// {
//     goalOrientation = 50;
// }




if(goalOrientation <10 && goalOrientation > 2){
    goalAngle = Orientation + 10;
}
else if(goalOrientation >-10 && goalOrientation < -2){
    goalAngle = Orientation - 10;
}
else if(goalOrientation <25 && goalOrientation >= 10){
    goalAngle = Orientation + 25;
}
else if(goalOrientation >-25 && goalOrientation <= -10){
    goalAngle = Orientation - 25;
}
else if(goalOrientation <35 && goalOrientation >= 25){
    goalAngle = Orientation + 35;
}
else if(goalOrientation >-35 && goalOrientation <= -25){
    goalAngle = Orientation - 35;
}
else if(goalOrientation <45 && goalOrientation >= 35){
    goalAngle = Orientation + 45;
}
else if(goalOrientation >-45 && goalOrientation <= -35){
    goalAngle = Orientation - 45;
}
else if(goalOrientation <55 && goalOrientation >= 45){
    goalAngle = Orientation + 55;
}
else if(goalOrientation >-55 && goalOrientation <= -45){
    goalAngle = Orientation - 55;
}
else if(goalOrientation <65 && goalOrientation >= 55){
    goalAngle = Orientation + 65;
}
else if(goalOrientation >-65 && goalOrientation <= -55){
    goalAngle = Orientation - 65;
}
else if(goalOrientation <75 && goalOrientation >= 65){
    goalAngle = Orientation + 75;
}
else if(goalOrientation >-75 && goalOrientation <= -65){
    goalAngle = Orientation - 75;
}
else if(goalOrientation <85 && goalOrientation >= 75){
    goalAngle = Orientation + 85;
}
else if(goalOrientation >-85 && goalOrientation <= -75){
    goalAngle = Orientation - 85;
}
else{
    goalAngle = Orientation;
}

    


    if (goalAngle > 360)
    {
        goalAngle = goalAngle - 360;
    }
    else if (goalAngle < 0)
    {
        goalAngle = goalAngle + 360;
    }
   }
    Serial.print("goal Angle : ");
    Serial.println(goalAngle);
    

    
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