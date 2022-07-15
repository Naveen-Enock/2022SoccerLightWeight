#include <Defense.h>

Defense::Defense()
{
    defenseTick = 0;
    findLine = false;
    stop = false;
}

void Defense::defense(bool Switch, double ballAngle, int goalAngle, bool linePresent, int initialOrientation)
{

       if(goalAngle ==-5){

           goalAngle = initialOrientation + 180;
       }
       
       if(goalAngle >360){
           goalAngle = goalAngle-360;
       }
    ballAngleX = sin(toRadians(ballAngle));
    ballAngleY = cos(toRadians(ballAngle));
    goalAngleX = sin(toRadians(goalAngle));
    goalAngleY = cos(toRadians(goalAngle));

    robotAngleX = ballAngleX + goalAngleX;
    robotAngleY = ballAngleY + goalAngleY;

    defenseAngle = toDegrees(atan2(robotAngleX, robotAngleY));
    if (defenseAngle < 0)
    {

        defenseAngle = defenseAngle + 360;
    }

    if (defenseAngle > 280 || defenseAngle < 80)
    {
        vectorX = sin(toRadians(90));
        vectorY = cos(toRadians(90));

        dotProduct = (robotAngleX * vectorX) + (robotAngleY * vectorY);
        denominator = pow(vectorX, 2) + pow(vectorY, 2);
        robotAngleX = (dotProduct / denominator) * vectorX;
        robotAngleY = (dotProduct / denominator) * vectorY;

        defenseAngle = toDegrees(atan2(robotAngleX, robotAngleY));
        if (defenseAngle < 0)
        {
            defenseAngle = defenseAngle + 360;
        }

    }

//     if(linePresent == false && defenseTick > 20000){
// findLine = true;

//     }
    if (findLine == true)
    {
       defenseAngle = 180;
       if(linePresent == true){
           findLine = false;
           defenseTick = 0;
       }
    }
    else{
    ++defenseTick;
    }
    angleDiff = abs(ballAngle - goalAngle);
         if (angleDiff > 180)
        {
            angleDiff = 360 - angleDiff;
        }
    if((angleDiff > 180 && angleDiff < 188)||(angleDiff<=180 && angleDiff>172))
    {
        stop = true;
    }
    else{
        stop = false;
    }
    Serial.print("defense Tick : ");
    Serial.println(defenseTick);
    Serial.print("defense angle : ");
    Serial.println(defenseAngle);
    Serial.print("ball angle: ");
    Serial.println(ballAngle);
    Serial.print("goal angle: ");
    Serial.println(goalAngle);
}