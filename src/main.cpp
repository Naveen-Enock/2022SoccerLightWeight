#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <ballAngle.h>
#include <motor.h>
#include <lineSensor.h>
#include <compassSensor.h>


int buttonState = 0;
BallAngle ballAngle;
Motor motor;
LineSensor lineSensor;
CompassSensor compassSensor;
int initialOrientation = compassSensor.getOrientation();
void setup()
{
  Serial.begin(9600);

  // pinMode(10,OUTPUT);
  pinMode(9, INPUT_PULLUP);
  // pinMode(14,INPUT);
}

void loop()
{
  //  int *values = lineSensor.GetValues();
  int buttonState = digitalRead(9);
  // Serial.print("Button state: ");
  // Serial.println (buttonState);


      ballAngle.Process();
      motor.Move(ballAngle.robotAngle, compassSensor.getOrientation(), initialOrientation);
      delay(1);


    // digitalWrite(28, HIGH);
    // digitalWrite(33, HIGH);
    // analogWrite(29, 0);
    // analogWrite(15, 0);
    // digitalWrite(6, HIGH);
    // digitalWrite(4, HIGH);
    // analogWrite(5, 0);
    // analogWrite(3, 0);

}
