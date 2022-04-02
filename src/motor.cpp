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
    Serial.println(robotAngle);
    double powerFR = 0;
    double powerFL = 0;
    double powerRR = 0;
    double powerRL = 0;
    int dirFR = LOW;
    int dirFL = LOW;
    int dirRR = LOW;
    int dirRL = LOW;

    powerFR = sin(toRadians(robotAngle - 50));
    powerRR = sin(toRadians(robotAngle - 130));
    powerRL = sin(toRadians(robotAngle - 230));
    powerFL = sin(toRadians(robotAngle - 310));

    double maxval = max(max(abs(powerFR),abs(powerFL)),max(abs(powerRR),abs(powerFL)));

    Serial.print( "PowerRR : ") ;
    Serial.print(powerRR);
    Serial.print(" DirRR : ");
    Serial.println(dirRR);

    Serial.print( "PowerRL : ") ;
    Serial.print(powerRL);
    Serial.print(" DirRL : ");
    Serial.println(dirRL);

    Serial.print( "PowerFR : ") ;
    Serial.print(powerFR);
    Serial.print(" DirFR : ");
    Serial.println(dirFR);

    Serial.print( "PowerFL : ") ;
    Serial.print(powerFL);
    Serial.print(" DirFL : ");
    Serial.println(dirFL);

    if (powerFR < 0)
    {
        dirFR = LOW;
        powerFR = powerFR/maxval;
        powerFR = -255*powerFR;
    }
    else
    {
        dirFR = HIGH;
        powerFR = powerFR/maxval;
        powerFR = 255*powerFR;
    }

    if (powerFL < 0)
    {
        dirFL = LOW;
       
        powerFL = powerFL/maxval;
        powerFL = -255*powerFL;
    }
    else
    {
        dirFL = HIGH;
        
        powerFL = powerFL/maxval;
        powerFL = 255*powerFL;
    }

    if (powerRL < 0)
    {
        dirRL = LOW;
        
        powerRL = powerRL/maxval;
        powerRL = -255*powerRL;
    }
    else
    {
        dirRL = HIGH;
       
        powerRL = powerRL/maxval;
        powerRL = 255*powerRL;
    }

    if (powerRR < 0)
    {
        dirRR = LOW;
        
        powerRR = powerRR/maxval;
        powerRR = -255*powerRR;
    }
    else
    {
        dirRR = HIGH;
        
        powerRR = powerRR/maxval;
        powerRR = 255*powerRR;
    }

 
    Serial.print( "PowerRR : ") ;
    Serial.print(powerRR);
    Serial.print(" DirRR : ");
    Serial.println(dirRR);

    Serial.print( "PowerRL : ") ;
    Serial.print(powerRL);
    Serial.print(" DirRL : ");
    Serial.println(dirRL);

    Serial.print( "PowerFR : ") ;
    Serial.print(powerFR);
    Serial.print(" DirFR : ");
    Serial.println(dirFR);

    Serial.print( "PowerFL : ") ;
    Serial.print(powerFL);
    Serial.print(" DirFL : ");
    Serial.println(dirFL);
 
    digitalWrite(controlRR, dirRR);
    digitalWrite(controlFR, dirFR);
    analogWrite(speedRR, powerRR);
    analogWrite(speedFR, powerFR);
    digitalWrite(controlFL, dirFL);
    digitalWrite(controlRL, dirRL);
    analogWrite(speedFL, powerFL);
    analogWrite(speedRL, powerRL);
}