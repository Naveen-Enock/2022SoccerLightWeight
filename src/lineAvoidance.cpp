#include <lineAvoidance.h>
#include <trig.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>

LineAvoidance::LineAvoidance()
{
    lowestval = 1024;
    highestval = 0;
    sensorAngle = -1;
    anglebisc = -1;
    chord = -1;
    initialAngle = -1;
    
}

void LineAvoidance::angle()
{
    lineValues = lineSensor.GetValues();
    sensorAngles = lineSensor.LineAngle();
    for (int i = 0; i < 24; i++)
    {
        if (lineValues[i] < 70)
        {
            lineValues[i] = 0;
            sensorAngles[i] = 0;
        }
        if (lowestval > lineValues[i] && lineValues[i] != 0)
        {
            lowestval = lineValues[i];
        }
        else if (highestval < lineValues[i])
        {
            highestval = lineValues[i];
        }
    }

    sensorAngle = highestval - lowestval;
    if (sensorAngle > 180)
    {
        sensorAngle = 360 - sensorAngle;
        anglebisc = sensorAngle / 2;
        anglebisc = (highestval + anglebisc);
        if (anglebisc > 360)
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
    chord = 2 * (0.5 * sin(toRadians(sensorAngle / 2)));
    
}

void LineAvoidance::Power(bool ball)
{
    if (ball == true && chordlength <= 1)
    {
        chordlength = 0;
    }
    else if (chord > 1)
    {
        chordlength = chordlength - 1;
    }

    lineFR = sin(toRadians(lineAngle - 40));
    lineRR = sin(toRadians(lineAngle - 140));
    lineRL = sin(toRadians(lineAngle - 220));
    lineFL = sin(toRadians(lineAngle - 320));

    double maxPower = max(max(abs(lineFR), abs(lineFL)), max(abs(lineRR), abs(lineFL)));

    lineFR = (lineFR*chordlength)/maxPower;
    lineRR = (lineRR*chordlength)/maxPower;
    lineRL = (lineRL*chordlength)/maxPower;
    lineFL = (lineFL*chordlength)/maxPower;
}



void LineAvoidance::Process(bool ball)
{
    angle();
    if (highestval>0)
    {
        if (initialAngle == -1)
        {
            initialAngle = anglebisc;
        }
        currentAngle = anglebisc;
        angleDiff = abs(currentAngle-initialAngle);
        if (angleDiff > 180)
        {
            angleDiff = 360-angleDiff;
        }
        else if (angleDiff <90)
        {
            lineAngle = anglebisc;
            Chord();
            chordlength = chord;
            Power(ball);
        }
        else if (angleDiff >90 )
        {
            lineAngle = lineAngle + 180;
            if (lineAngle >360)
            {
                lineAngle = lineAngle-360;
            }
            Chord();
            chordlength = 2-chord;
            Power(ball);
        }
        
    }
    else if (highestval==0 && lowestval==0)
    {
        initialAngle = -1;
        lineAngle = 0;
        chordlength = 0;
    }
    
    
}