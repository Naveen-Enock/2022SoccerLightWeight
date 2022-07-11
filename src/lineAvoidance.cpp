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

    lineSwitch = false;
    outOfBounds = false;
}

void LineAvoidance::angle(int *calibrateVal, int *lineVal, int *sensorVal)
{
    lowestval = 1024;
    highestval = -1;
    lineValues = lineVal;
    sensorAngles = sensorVal;
    
    linepresent = false;
    for (int i = 0; i < 24; i++)
    {
        
        if (lineValues[i] < calibrateVal[i])
        {

            sensorAngles[i] = -1;
  
        }
        //           Serial.print(i);
        // Serial.print("line : ");
        // Serial.println(calibrateVal[i]);
        if (lowestval > sensorAngles[i] && sensorAngles[i] != -1)
        {
            lowestval = sensorAngles[i];
        }
        if (highestval < sensorAngles[i])
        {
            highestval = sensorAngles[i];
        }
        if (sensorAngles[i] > -1)
        {
            linepresent = true;
        }
        //  Serial.print(i);
        //  Serial.print("line : ");
        //  Serial.println(lineValues[i]);
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
    Serial.print("Angle Bisc : ");
    Serial.println(anglebisc);
}

void LineAvoidance::Chord()
{
    chord = 2 * (0.5 * sin(toRadians(sensorAngle / 2)));
    
}

void LineAvoidance::Power(bool ball)
{
    if (linepresent == true)
    {

 
        lineFR = sin(toRadians(lineAngle - 40));
        lineRR = sin(toRadians(lineAngle - 130));
        lineRL = sin(toRadians(lineAngle - 230));
        lineFL = sin(toRadians(lineAngle - 310));

        double maxPower = max(max(abs(lineFR), abs(lineFL)), max(abs(lineRR), abs(lineFL)));

        lineFR = (lineFR / maxPower);
        lineRR = (lineRR / maxPower);
        lineRL = (lineRL / maxPower);
        lineFL = (lineFL / maxPower);
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

void LineAvoidance::Process(bool ball, int *calibrateVal, int *lineVal, int *sensorVal)
{
    angle(calibrateVal, lineVal, sensorVal);
    if (linepresent == true)
    {
        outOfBounds = false;
        if (initialAngle == -1 )
        {
            initialAngle = anglebisc;
        }
        currentAngle = anglebisc;
        Serial.print("intial : ");
        Serial.println(initialAngle);
        Serial.print("current : ");
        Serial.println(currentAngle);
        angleDiff = abs(currentAngle - initialAngle);
        initialAngle = currentAngle;
        if (angleDiff > 180)
        {
            angleDiff = 360 - angleDiff;
        }
        Serial.print("Diff : ");
        Serial.println(angleDiff);
        if (angleDiff > 100 && angleDiff <= 180 && lineSwitch == false){
            lineSwitch = true;
            angleDiff = 0;
        }

        if (lineSwitch == true)
        {

            lineAngle = anglebisc;
            Chord();
            chordlength = 2 - chord;

            if (angleDiff > 100 && angleDiff <= 180)
            {
                lineSwitch = false;
            }
        }

        if (lineSwitch == false)
        {
            lineAngle = anglebisc + 180;
            if (lineAngle >= 360)
            {
                lineAngle = lineAngle - 360;
            }
            Chord();
            chordlength = chord;
        }

        lineFR = 0;
        lineRR = 0;
        lineRL = 0;
        lineFL = 0;
        projectionState = false;
projectionAngle = anglebisc + 90;
  if (projectionAngle > 360)
            {
                projectionAngle = projectionAngle - 360;
            }
        if (chordlength > 0 && chordlength < 0.5)
        {
            projectionState = true;
            
       
             Serial.print("projectionAngle : ");
        Serial.println(projectionAngle);
        }
        else if (chordlength >= 0.5)
        {
            Power(ball);
        }
       Serial.print("lineAngle : ");
        Serial.println(lineAngle);
        
        Serial.print("chordlength : ");
        Serial.println(chordlength);
        // Serial.print("Initial : ");
        // Serial.println(initialAngle);
    }
    else if (linepresent == false)
    {
        if(lineSwitch == true)
        {
           outOfBounds = true; 
           initialAngle = -1;
           Power(ball);
        }
        
        else{
        initialAngle = -1;
        lineAngle = -1;
        chordlength = 0;
        lineSwitch = false;
        lineFR = 0;
        lineRR = 0;
        lineRL = 0;
        lineFL = 0;
        projectionState = false;
        }
    }
}