#include <lineAvoidance.h>
#include <trig.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>

LineAvoidance::LineAvoidance()
{
    lowestval = 1024;
    highestval = -181;
    anglebisc = -1;
    chord = -1;
    initialAngle = -1;

    lineSwitch = false;
    outOfBounds = false;
    negativeLow = false;
    dotProduct = new double[24];
}

void LineAvoidance::angle(int *calibrateVal, int *lineVal, int *sensorVal, double *sinVal, double *cosVal)
{

    lineValues = lineVal;
    sensorAngles = sensorVal;
    negativeLow = false;

    linepresent = false;
    double *cosValues = cosVal;
    double *sinValues = sinVal;
    double totalCos = 0;
    double totalSin = 0;
    for (int i = 0; i < 24; i++)
    {
        // Serial.print(i);
        // Serial.print("line : ");
        // Serial.println(lineValues[i]);
        if (lineValues[i] < calibrateVal[i])
        {

            lineValues[i] = 0;
            dotProduct[i] = 0;
        }
        else
        {
            lineValues[i] = 1;
            linepresent = true;
            dotProduct[i] = sensorAngles[i];
        }

        //           Serial.print(i);
        // Serial.print("line : ");
        // Serial.println(calibrateVal[i]);

        
    }
 
    lowestDot = 2;
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            if (dotProduct[i] != 0 && dotProduct[j] != 0)
            {
                dot = (sinValues[i] * sinValues[j]) + (cosValues[i] * cosValues[j]);
                if (dot < lowestDot)
                {
                    lowestDot = dot;
                    firstAngle = i;
                    secondAngle = j;
                }
            }
        }
    }
    // Serial.print("Dot Produt");
    // Serial.println(lowestDot);
    //     Serial.print("first angle");
    // Serial.println(sensorAngles[firstAngle]);
    //     Serial.print("second angle");
    //Serial.println(sensorAngles[secondAngle]);
    totalCos = cosValues[firstAngle] + cosValues[secondAngle];
        totalSin = sinValues[firstAngle] + sinValues[secondAngle];
                
    anglebisc = toDegrees(atan2(totalCos, totalSin));
    sensorAngle = abs(sensorAngles[firstAngle]-sensorAngles[secondAngle]);
       if (sensorAngle > 180)
    {
        sensorAngle = 360 - sensorAngle;
    }

    if (totalCos == 0 && totalSin == 0)
    {
        anglebisc = initialAngle;
    }
    if (anglebisc < 0)
    {

        anglebisc = anglebisc + 360;
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

    lineFR = sin(toRadians(lineAngle - 40));
    lineRR = sin(toRadians(lineAngle - 130));
    lineRL = sin(toRadians(lineAngle - 230));
    lineFL = sin(toRadians(lineAngle - 310));

    double maxPower = max(max(abs(lineFR), abs(lineFL)), max(abs(lineRR), abs(lineFL)));

    lineFR = (lineFR / maxPower);
    lineRR = (lineRR / maxPower);
    lineRL = (lineRL / maxPower);
    lineFL = (lineFL / maxPower);

    // Serial.print("Power FR : ");
    // Serial.println(lineFR);
    // Serial.print("Power RR : ");
    // Serial.println(lineRR);
    // Serial.print("Power RL : ");
    // Serial.println(lineRL);
    // Serial.print("Power FL : ");
    // Serial.println(lineFL);
}

void LineAvoidance::Process(bool ball, int *calibrateVal, int *lineVal, int *sensorVal, double chordThreshold, double *sinVal, double *cosVal)
{
    angle(calibrateVal, lineVal, sensorVal, sinVal, cosVal);
    Serial.print("linePresent : ");
    Serial.println(linepresent);
    if (linepresent == true)
    {
        outOfBounds = false;
        if (initialAngle == -1)
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
        if (angleDiff > 90 && lineSwitch == false)
        {
            lineSwitch = true;
            angleDiff = 0;
        }

        if (lineSwitch == true)
        {

            lineAngle = anglebisc;
            Chord();
            chordlength = 2 - chord;

            if (angleDiff > 90)
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
        Serial.print("line Switch: ");
        Serial.println(lineSwitch);
        lineFR = 0;
        lineRR = 0;
        lineRL = 0;
        lineFL = 0;
        projectionState = false;

        if (chordlength > 0 && chordlength < chordThreshold)
        {
            projectionState = true;
        projectionAngle = anglebisc + 90;
        if (projectionAngle > 360)
        {
            projectionAngle = projectionAngle - 360;
        }
            Serial.print("projectionAngle : ");
            Serial.println(projectionAngle);
        }
        if (chordlength >= chordThreshold)
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
        if (lineSwitch == true)
        {
            Serial.println("hi");
            Serial.println(lineAngle);
            outOfBounds = true;
            initialAngle = -1;
            Power(ball);
        }

        else
        {
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