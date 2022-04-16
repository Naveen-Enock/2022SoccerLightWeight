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

void Motor::Move(double robotAngle)
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
    

    powerFR = sin(toRadians(robotAngle - 40)) ;
    powerRR = sin(toRadians(robotAngle - 140)) ;
    powerRL = sin(toRadians(robotAngle - 220));
    powerFL = sin(toRadians(robotAngle - 320));

    double maxval = max(max(abs(powerFR),abs(powerFL)),max(abs(powerRR),abs(powerFL)));

    GetMotorDirectionAndSpeed(dirFR,powerFR,maxval);
    GetMotorDirectionAndSpeed(dirFL,powerFL,maxval);
    GetMotorDirectionAndSpeed(dirRR,powerRR,maxval);
    GetMotorDirectionAndSpeed(dirRL,powerRL,maxval);
 
    
    
    digitalWrite(controlRR, dirRR);
    digitalWrite(controlFR, dirFR);
    analogWrite(speedRR, powerRR);
    analogWrite(speedFR, powerFR);
    digitalWrite(controlFL, dirFL);
    digitalWrite(controlRL, dirRL);
    analogWrite(speedFL, powerFL);
    analogWrite(speedRL, powerRL);
}

void Motor::GetMotorDirectionAndSpeed(int &direction, double &power,double maxValue)
{
    direction = power < 0 ? LOW : HIGH;
    power = 255 * abs(power)/maxValue;
}