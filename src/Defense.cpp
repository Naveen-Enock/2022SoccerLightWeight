#include <Defense.h>

Defense::Defense()
{
}

void Defense::defense(int lineAngle, double ballAngle, int goalAngle, bool linePresent)
{
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
    Serial.print("defense angle : ");
    Serial.println(defenseAngle);
    Serial.print("ball angle: ");
    Serial.println(ballAngle);
    Serial.print("goal angle: ");
    Serial.println(goalAngle);
}