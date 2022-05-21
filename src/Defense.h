#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Defense
{
public:
    Defense();
    void defense(int lineAngle, double ballAngle, bool linePresent, bool lineSwitch);
    double defenseAngle;
    double newLineAngle;

private:
    double bVal;
    double sVal;
    double oppositeAngle;
    double smalloppositeAngle;
    double bigoppositeAngle;
    int realballAngle;
    double realoppositeAngle;
    int reAlign;
    bool reallineSwitch;
    int angleAdd;
    int compareAngle;
};