#include <lineAvoidance.h>
#include <trig.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>

LineAvoidance::LineAvoidance()
{
    lowestval = 1024;
    highestval = -1;
    anglebisc = -1;
    chord = -1;
    initialAngle = -1;
    initialWait = 0;
}

void LineAvoidance::angle()
{

    lineValues = lineSensor.GetValues();
    sensorAngles = lineSensor.LineAngle();

    for (int i = 0; i < 24; i++)
    {

        if (lineValues[i] < 46)
        {

            sensorAngles[i] = -1;
        }

        if (lowestval > sensorAngles[i] && sensorAngles[i] != -1)
        {
            lowestval = sensorAngles[i];
        }
        if (highestval < sensorAngles[i])
        {
            highestval = sensorAngles[i];
        }
        // Serial.print(i);
        // Serial.print("line : ");
        // Serial.println(lineValues[i]);
    }
    Serial.print("lowest : ");
    Serial.println(lowestval);
    Serial.print("highest : ");
    Serial.println(highestval);
    sensorAngle = highestval - lowestval;
    if (sensorAngle > 180)
    {
        sensorAngle = 360 - sensorAngle;
        anglebisc = sensorAngle / 2;
        anglebisc = (highestval + anglebisc);
        if (anglebisc >= 360)
        {
            anglebisc = anglebisc - 360;
        }
    }
    else
    {
        anglebisc = sensorAngle / 2;
        anglebisc = lowestval + anglebisc;
    }
}

void LineAvoidance::Chord()
{
    chord = 2 * (1.25 * sin(toRadians(sensorAngle / 2)));

}

void LineAvoidance::Power(bool ball)
{
    if (linepresent == true)
    {


        Serial.print("lineAngle : ");
        Serial.println(lineAngle);
        Serial.print("chordlength : ");
        Serial.println(chordlength);
        lineFR = sin(toRadians(lineAngle - 40));
        lineRR = sin(toRadians(lineAngle - 140));
        lineRL = sin(toRadians(lineAngle - 220));
        lineFL = sin(toRadians(lineAngle - 320));

        double maxPower = max(max(abs(lineFR), abs(lineFL)), max(abs(lineRR), abs(lineFL)));

        lineFR = (lineFR * chordlength) / maxPower;
        lineRR = (lineRR * chordlength) / maxPower;
        lineRL = (lineRL * chordlength) / maxPower;
        lineFL = (lineFL * chordlength) / maxPower;
    }
    else if (linepresent == false)
    {
        lineFR = 0;
        lineRR = 0;
        lineRL = 0;
        lineFL = 0;
    }
    // Serial.print("Power FR : ");
    // Serial.println(lineFR);
    // Serial.print("Power RR : ");
    // Serial.println(lineRR);
    // Serial.print("Power RL : ");
    // Serial.println(lineRL);
    // Serial.print("Power FL : ");
    // Serial.println(lineFL);
}

void LineAvoidance::Process(bool ball)
{
    angle();
    if (lowestval < 1024)
    {
        linepresent = true;
        if (initialAngle == -1)
        {
            initialAngle = anglebisc;
        }
        currentAngle = anglebisc;
        angleDiff = abs(currentAngle - initialAngle);
        if (angleDiff > 180)
        {
            angleDiff = 360 - angleDiff;
        }

        if (angleDiff > 110 && angleDiff <= 180)
        {
            lineSwitch = true;
            lineAngle = anglebisc;
            anglebisc = anglebisc+180;
            if(anglebisc > 360)
            {
                anglebisc = anglebisc - 360;
            }
            Chord();
            chordlength = 5 - chord;
            
        }
        else if (angleDiff < 110)
        {
            lineSwitch = false;
            lineAngle = anglebisc + 180;
            if (lineAngle >= 360)
            {
                lineAngle = lineAngle - 360;
            }
            Chord();
            chordlength = chord;
        }
Serial.print("Diff : ");
Serial.println(angleDiff);
Serial.print("Initial : ");
Serial.println(initialAngle);
//initialWait = 0;
        lowestval = 1024;
        highestval = -1;
    }
    else if (highestval == -1 && lowestval == 1024)
    {

        initialAngle = -1;
        linepresent = false;
        lineAngle = 0;
        chordlength = 0;
        lowestval = 1024;
        highestval = -1;


    }

    Power(ball);
}