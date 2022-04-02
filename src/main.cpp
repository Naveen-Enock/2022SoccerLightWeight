#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <ballAngle.h>
#include <motor.h>
#include <lineSensor.h>





int buttonState = 0; 
BallAngle ballAngle; 
Motor motor;
LineSensor lineSensor;

void setup() {
  Serial.begin(9600);



  // pinMode(10,OUTPUT);
  // pinMode(9,INPUT_PULLUP);
  // pinMode(14,INPUT);
   
}

void loop() {
 int *values = lineSensor.GetValues(); 
  ballAngle.Process();
   motor.Move(ballAngle.robotAngle);
  delayMicroseconds(1000);
  delay(1000);
}