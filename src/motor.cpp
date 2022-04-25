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
};

void Motor::Move(double robotAngle, double orientation, double initialOrientation)
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
    double orientationVal = orientation - initialOrientation;
    if (orientation > 180)
    {
        orientationVal = orientationVal - 360;
    }

    Serial.print("Val : ");
    Serial.println(orientationVal);

    double correction = -1 * (sin(toRadians(orientationVal)));
    if (orientationVal > -5)
    {
        if (orientationVal < 0)
        {
            correction = 0;
        }
    }
    if (orientationVal < 5)
    {
        if (orientationVal > 0)
        {
            correction = 0;
        }
    }
    if (orientationVal >90){
        correction =-1;
    }
        if (orientationVal <-90){
        correction =1;
    }

    Serial.println();
    Serial.println("Correction : ");
    Serial.println(correction);

    powerFR = sin(toRadians(robotAngle - 40)) + correction;
    powerRR = sin(toRadians(robotAngle - 140)) + correction;
    powerRL = sin(toRadians(robotAngle - 220)) + correction;
    powerFL = sin(toRadians(robotAngle - 320)) + correction;

    double maxval = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerFL)));

    GetMotorDirectionAndSpeed(dirFR, powerFR, maxval);
    GetMotorDirectionAndSpeed(dirFL, powerFL, maxval);
    GetMotorDirectionAndSpeed(dirRR, powerRR, maxval);
    GetMotorDirectionAndSpeed(dirRL, powerRL, maxval);

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
    direction = power < 0 ? LOW : HIGH;
    power = 255 * abs(power) / maxValue;
}