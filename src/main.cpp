#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <ballAngle.h>
#include <motor.h>

int adcpin4 = 23;
int adcpin5 = 22;
int adcpin6 = 21;
int channel = 6;
int value;

MCP3008 adc4;
MCP3008 adc5;
MCP3008 adc6;

int buttonState = 0; 
BallAngle ballAngle; 
Motor motor;


void setup() {
  Serial.begin(9600);

  // adc4.begin(adcpin4,11,12,13);
  // adc5.begin(adcpin5,11,12,13);
  // adc6.begin(adcpin6,11,12,13);

  // pinMode(10,OUTPUT);
  // pinMode(9,INPUT_PULLUP);
  // pinMode(14,INPUT);
  
 
  
}



void loop() {

  ballAngle.Process();
   motor.Move(ballAngle.robotAngle);
  delay(1);


}