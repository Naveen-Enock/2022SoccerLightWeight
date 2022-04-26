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
void Motor::Orientation(double orientation, double initialOrientation)
{
    double orientationVal;
    orientationVal = orientation - initialOrientation;
    if (orientationVal > 180)
    {
        orientationVal = -1 * (360 - orientationVal);
    }

    Serial.print("Val : ");
    Serial.println(orientationVal);

    correction = -1 * (sin(toRadians(orientationVal)));
    if (orientationVal > -5 && orientationVal < 0)
    {
        correction = 0;
    }
    else if (orientationVal < 5 && orientationVal > 0)
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

    Serial.println();
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
    double ballFR = 0;
    double ballFL = 0;
    double ballRR = 0;
    double ballRL = 0;

    int dirFR = LOW;
    int dirFL = LOW;
    int dirRR = LOW;
    int dirRL = LOW;

    Orientation(orientation, initialOrientation);
    ballFR = sin(toRadians(robotAngle - 40));
    ballRR = sin(toRadians(robotAngle - 140));
    ballRL = sin(toRadians(robotAngle - 220));
    ballFL = sin(toRadians(robotAngle - 320));
    if (ballpresent == false)
    {
        ballFR = 0;
        ballRR = 0;
        ballRL = 0;
        ballFL = 0;
    }

    powerFR = ballFR + correction+lineFR;
    powerRR = ballRR + correction+lineRR;
    powerRL = ballRL + correction+lineRL;
    powerFL = ballFL + correction+lineFL;

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