#include <Defense.h>

Defense::Defense()
{
    newLineAngle = 180;
    compareAngle = 180;
}

void Defense::defense(int lineAngle, double ballAngle, bool linePresent, bool lineSwitch)
{
    realballAngle = ballAngle;
    if (realballAngle < 180)
    {
        realballAngle = realballAngle + 360;
    }
    bVal = lineAngle + 90;
    sVal = lineAngle - 90;
    oppositeAngle = lineAngle + 180;

    if (oppositeAngle > 360)
    {
        oppositeAngle = oppositeAngle - 360;
    }
    smalloppositeAngle = oppositeAngle;
    bigoppositeAngle = oppositeAngle;
    if (bVal > 360)
    {
        bVal = bVal - 360;
    }
    if (sVal < 0)
    {
        sVal = sVal + 360;
    }
    if (smalloppositeAngle > 180)
    {
        smalloppositeAngle = smalloppositeAngle - 360;
    }
    if (bigoppositeAngle < 180)
    {
        bigoppositeAngle = bigoppositeAngle + 360;
    }
    if (ballAngle < sVal && ballAngle > smalloppositeAngle)
    {

        ballAngle = abs(oppositeAngle - ballAngle);
        if (ballAngle > 180)
        {
            ballAngle = 360 - ballAngle;
        }
        if (ballAngle < 50)
        {
            ballAngle = 50;
        }
        else if (ballAngle > 70)
        {
            ballAngle = 70;
        }
        defenseAngle = lineAngle - ballAngle;
        if (lineSwitch == true)
        {
            defenseAngle = defenseAngle - 90;
        }
        if (defenseAngle < 0)
        {
            defenseAngle = defenseAngle + 360;
        }
    }

    else if (ballAngle > bVal && ballAngle < bigoppositeAngle)
    {

        ballAngle = abs(oppositeAngle - ballAngle);
        if (ballAngle > 180)
        {
            ballAngle = 360 - ballAngle;
        }
        if (ballAngle < 50)
        {
            ballAngle = 50;
        }
        else if (ballAngle > 70)
        {
            ballAngle = 70;
        }
        defenseAngle = lineAngle + ballAngle;
        if (lineSwitch == true)
        {
            defenseAngle = defenseAngle + 90;
        }
        if (defenseAngle > 360)
        {
            defenseAngle = defenseAngle - 360;
        }
    }
    else if (ballAngle < bVal && ballAngle > lineAngle)
    {
        ballAngle = abs(lineAngle - ballAngle);

        if (ballAngle > 180)
        {
            ballAngle = 360 - ballAngle;
        }
        if (ballAngle < 50)
        {
            ballAngle = 50;
        }
        else if (ballAngle > 70)
        {
            ballAngle = 70;
        }
        defenseAngle = lineAngle + ballAngle;
        if (lineSwitch == true)
        {
            defenseAngle = defenseAngle + 90;
        }
        if (defenseAngle > 360)
        {
            defenseAngle = defenseAngle - 360;
        }
    }
    else if (ballAngle > sVal && ballAngle < lineAngle)
    {
        ballAngle = abs(lineAngle - ballAngle);
        if (ballAngle > 180)
        {
            ballAngle = 360 - ballAngle;
        }
        if (ballAngle < 50)
        {
            ballAngle = 50;
        }
        else if (ballAngle > 70)
        {
            ballAngle = 70;
        }
        defenseAngle = lineAngle - ballAngle;
        if (lineSwitch == true)
        {
            defenseAngle = defenseAngle - 90;
        }
        if (defenseAngle < 0)
        {
            defenseAngle = defenseAngle + 360;
        }
    }

    if (linePresent == true)
    {
        newLineAngle = lineAngle;
        realoppositeAngle = bigoppositeAngle;
        reallineSwitch = lineSwitch;
    }
    else if (linePresent == false)
    {
        reAlign = 180 - newLineAngle;
        angleAdd = max(0, reAlign + 45);



        if (realballAngle < realoppositeAngle)
        {
        if (reallineSwitch == true)
        {
            
            newLineAngle = newLineAngle + 180;
            reAlign = 360 - newLineAngle;
            angleAdd = min(45,reAlign-45);
            
        }
            defenseAngle = newLineAngle + angleAdd;
            if (defenseAngle > 360)
            {
                defenseAngle = defenseAngle - 360;
            }
        }
        else
        {

            angleAdd = max(-45, reAlign - 45);
        if (reallineSwitch == true)
        {
            
            newLineAngle = newLineAngle + 180;
            reAlign = 360 - newLineAngle;
            angleAdd = max(-45,reAlign+45);
            
        }
            defenseAngle = newLineAngle + angleAdd;
            if(defenseAngle>360)
            {
                defenseAngle = defenseAngle - 360;
            }
        }
    }
    Serial.print("DefenseAngle: ");
    Serial.println(defenseAngle);
    Serial.print("ballAngle : ");
    Serial.println(ballAngle);
    Serial.print("lineAngle : ");
    Serial.println(lineAngle);
    Serial.print("big Val: ");
    Serial.println(bVal);
    Serial.print("Smal Val : ");
    Serial.println(sVal);
    Serial.print("bigOpposite : ");
    Serial.println(bigoppositeAngle);
    Serial.print("smallOpposite : ");
    Serial.println(smalloppositeAngle);
}