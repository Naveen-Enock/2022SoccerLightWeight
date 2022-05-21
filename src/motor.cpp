#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <trig.h>

Motor::Motor()
{
    speedRR = 29;
    speedFR = 15;
    speedFL = 5;
    speedRL = 3;
    controlRR = 28;
    controlFR = 33;
    controlFL = 6;
    controlRL = 4;
    pinMode(speedFR, OUTPUT);
    pinMode(speedFL, OUTPUT);
    pinMode(speedRR, OUTPUT);
    pinMode(speedRL, OUTPUT);
    pinMode(controlRR, OUTPUT);
    pinMode(controlRL, OUTPUT);
    pinMode(controlFR, OUTPUT);
    pinMode(controlFL, OUTPUT);
    maxval = 0;
};
void Motor::Orientation(double orientation, double initialOrientation)
{
    double orientationVal;
    if (initialOrientation <180  && orientation > 180)
    {
        orientation = -1*(360-orientation);
    }
    if (initialOrientation > 180 && orientation < 180)
    {
        orientation = (orientation + 360);
    }
    orientationVal = abs(orientation - initialOrientation);

    Serial.println(orientationVal);
    if (orientationVal > 180)
    {
        orientationVal = (360 - orientationVal);
    }

    if (orientation < initialOrientation)
    {
        orientationVal = -1*orientationVal;
    }


    correction = -1 * (sin(toRadians(orientationVal)));

    if (orientationVal > -8 && orientationVal < 0)
    {
        correction = 0;
    }
    else if (orientationVal < 8 && orientationVal > 0)
    {
        correction = 0;
    }
    else if (orientationVal > 90)
    {
        correction = -1;
    }
    else if (orientationVal < -90)
    {
        correction = 1;
    }
    // if (correction<0.5 && correction >0)
    // {
    //     correction = 0.5;
    // }
    // else if (correction>-0.5 && correction <0)
    // {
    //     correction = -0.5;
    // }
    
    

    Serial.println("Correction : ");
    Serial.println(correction);
}
void Motor::Move(bool ballpresent, double robotAngle, double orientation, double initialOrientation,double lineFR, double lineRR, double lineRL, double lineFL)
{


    Logln(robotAngle);
    double powerFR = 0;
    double powerFL = 0;
    double powerRR = 0;
    double powerRL = 0;

    int dirFR = LOW;
    int dirFL = LOW;
    int dirRR = LOW;
    int dirRL = LOW;
Orientation(orientation, initialOrientation);
    
    powerFR = sin(toRadians(robotAngle - 40));
    powerRR = sin(toRadians(robotAngle - 140));
    powerRL = sin(toRadians(robotAngle - 220));
    powerFL = sin(toRadians(robotAngle - 320));
    if (ballpresent == false)
    {
        powerFR = 0;
        powerRR = 0;
        powerRL = 0;
        powerFL = 0;
    }
//Serial.println(correction);
powerFR = powerFR ;
powerRR = powerRR ;
powerRL = powerRL ;
powerFL = powerFL ;
    
    maxval = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerFL)));

    GetMotorDirectionAndSpeed(dirFR, powerFR, maxval);
    GetMotorDirectionAndSpeed(dirFL, powerFL, maxval);
    GetMotorDirectionAndSpeed(dirRR, powerRR, maxval);
    GetMotorDirectionAndSpeed(dirRL, powerRL, maxval);



    powerFR = powerFR + lineFR + correction;
    powerRR = powerRR + lineRR + correction;
    powerRL = powerRL + lineRL + correction;
    powerFL = powerFL + lineFL + correction;
    Serial.print("Power FR : ");
    Serial.println(powerFR);
    Serial.println(dirFR);
    Serial.print("Power RR : ");
    Serial.println(powerRR);
    Serial.println(dirRR);  
    Serial.print("Power RL : ");
    Serial.println(powerRL); 
    Serial.println(dirRL);
    Serial.print("Power FL : ");
    Serial.println(powerFL); 
    Serial.println(dirFL);
    // Serial.print("Power FR : ");
    // Serial.println(powerFR);
    // Serial.println(lineFR);
    // Serial.print("Power RR : ");
    // Serial.println(powerRR);
    // Serial.println(lineRR);  
    // Serial.print("Power RL : ");
    // Serial.println(powerRL); 
    // Serial.println(lineRL);
    // Serial.print("Power FL : ");
    // Serial.println(powerFL); 
    // Serial.println(lineFL);
    

maxval = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerFL)));

    
    GetMotorDirectionAndRealSpeed(dirFR, powerFR, maxval);
    GetMotorDirectionAndRealSpeed(dirFL, powerFL, maxval);
    GetMotorDirectionAndRealSpeed(dirRR, powerRR, maxval);
    GetMotorDirectionAndRealSpeed(dirRL, powerRL, maxval);



    digitalWrite(controlRR, dirRR);
    digitalWrite(controlFR, dirFR);
    analogWrite(speedRR, powerRR);
    analogWrite(speedFR, powerFR);
    digitalWrite(controlFL, dirFL);
    digitalWrite(controlRL, dirRL);
    analogWrite(speedFL, powerFL);
    analogWrite(speedRL, powerRL);
}

void Motor::GetMotorDirectionAndSpeed(int &direction, double &power, double maxValue)
{
    
    if (maxValue == 0)
    {
        power = 0;

    }

    
    else
    {
    power = power / maxValue;
    direction = power < 0 ? LOW : HIGH;
    }
    

}

void Motor::GetMotorDirectionAndRealSpeed(int &direction, double &power,double maxValue )
{
if (maxValue == 0)
{
    power = 0;
}
    else if (maxValue <=1)
    {
        direction = power < 0 ? LOW : HIGH;
        power = 255*abs(power);
        
    }
else{
direction = power < 0 ? LOW : HIGH;
power = 255 * ((abs(power)) / maxValue);

}
}