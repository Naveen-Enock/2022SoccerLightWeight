#include <motor.h>
#include <Arduino.h>
#include <math.h>
#include <string.h>
#include <trig.h>

Motor::Motor()
{
    speedRR = 5;
    speedFR = 29;
    speedFL = 3;
    speedRL = 28;
    controlRR = 6;
    controlFR = 15;
    controlFL = 4;
    controlRL = 33;
    
    
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

    orientationVal = abs(orientation - initialOrientation);

    Serial.println(orientationVal);
    if (orientationVal > 180)
    {
        orientationVal = 360 - orientationVal;
    }
    if (initialOrientation <180  && orientation > 180)
    {
        orientation = -1*(360-orientation);
    }
    else if (initialOrientation > 180 && orientation < 180)
    {
        orientation = (orientation + 360);
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

    
    

    Serial.println("Correction : ");
    Serial.println(correction);
}

void Motor::LineFollow(double &robotAngle, int projectionAngle)
{


robotX = sin(toRadians(robotAngle));
robotY = cos(toRadians(robotAngle));
lineX = sin(toRadians(projectionAngle));
lineY = cos(toRadians(projectionAngle));


dotProduct = (robotX*lineX)+(robotY*lineY);
denominator = pow(lineX,2)+pow(lineY,2);
projectionX = (dotProduct/denominator)*lineX;
projectionY = (dotProduct/denominator)*lineY;

robotAngle = toDegrees(atan2(projectionX, projectionY));
if(robotAngle < 0)
{
    robotAngle += 360;
}
// Serial.print("Robot Angle(Motor) : ");
// Serial.println(robotAngle);
}
void Motor::Move(bool ballpresent, double robotAngle, double orientation, double initialOrientation,double lineFR, double lineRR, double lineRL, double lineFL, bool projectionState, int projectionAngle, bool defenseStop)
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

    if(projectionState == true)
{
LineFollow(robotAngle,projectionAngle);
}
Serial.print("Robot Angle : ");
Serial.println(robotAngle);

    powerFR = sin(toRadians(robotAngle - 40));
    powerRR = sin(toRadians(robotAngle - 130));
    powerRL = sin(toRadians(robotAngle - 230));
    powerFL = sin(toRadians(robotAngle - 310));
    if (ballpresent == false||defenseStop == true)
    {
        powerFR = 0;
        powerRR = 0;
        powerRL = 0;
        powerFL = 0;
        correction = 0;
        lineFR = 0;
        lineFL = 0;
        lineRR = 0;
        lineRL = 0;
    }
//Serial.println(correction);

    
     maxval = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerFL)));

     GetMotorDirectionAndSpeed(dirFR, powerFR, maxval);
     GetMotorDirectionAndSpeed(dirFL, powerFL, maxval);
     GetMotorDirectionAndSpeed(dirRR, powerRR, maxval);
     GetMotorDirectionAndSpeed(dirRL, powerRL, maxval);



    powerFR = powerFR  + correction;
    powerRR = powerRR  + correction;
    powerRL = powerRL  + correction;
    powerFL = powerFL  + correction;

if(lineFR != 0 || lineRR != 0 || lineRL != 0 || lineFL != 0)
{
powerFR = lineFR;
powerRR = lineRR;
powerRL = lineRL;
powerFL = lineFL;
}
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

maxval = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerFL)));

    // Serial.print("maxval : ");
    // Serial.println(maxval);
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

else{
direction = power < 0 ? LOW : HIGH;
power = 0.7*(255 * (abs(power) / maxValue));

}
}