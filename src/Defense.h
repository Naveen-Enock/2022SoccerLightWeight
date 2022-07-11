#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>
#include <trig.h>

class Defense
{
public:
    Defense();
    void defense(double highestVal, double ballAngle,int goalAngle, bool linePresent, int initialOrientation);
    double defenseAngle;
    double newLineAngle;
    boolean stop;

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
  int defenseTick;
  bool findLine;
  double angleDiff;
  

};