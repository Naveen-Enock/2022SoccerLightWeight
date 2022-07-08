#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>
#include <trig.h>

class Defense
{
public:
    Defense();
    void defense(int lineAngle, double ballAngle,int goalAngle, bool linePresent);
    double defenseAngle;
    double newLineAngle;

private:
  double ballAngleX;
  double ballAngleY;
  double goalAngleX;
  double goalAngleY;
  double vectorX;
  double vectorY;
  double dotProduct;
  double denominator;
  double robotAngleX;
  double robotAngleY;
  

};