#include <Defense.h>

Defense::Defense()
{
   
}

void Defense::defense(int lineAngle, double ballAngle,int goalAngle, bool linePresent)
{
    ballAngleX = sin(toRadians(ballAngle));
    ballAngleY = cos(toRadians(ballAngle));
    goalAngleX = sin(toRadians(goalAngle));
    goalAngleY = cos(toRadians(goalAngle));

    robotAngleX = ballAngleX + goalAngleX;
    robotAngleY = ballAngleY + goalAngleY;


    if(linePresent == true){
        lineAngleX = sin(toRadians(lineAngle));
        lineAngleY = cos(toRadians(lineAngle));

dotProduct = (robotAngleX*lineAngleX)+(robotAngleY*lineAngleY);
denominator = pow(lineAngleX,2)+pow(lineAngleY,2);
robotAngleX = (dotProduct/denominator)*lineAngleX;
robotAngleY = (dotProduct/denominator)*lineAngleY;
    }

    defenseAngle = toDegrees(atan2(robotAngleX,robotAngleY));
    
}