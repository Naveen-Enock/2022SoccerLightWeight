#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Xbee 
{
public:
Xbee();
double ballDist;
void role(double highestVal);
bool offenseRole;
void proximity();


private:


char transmit;
std::string transmitNum;
void sendData(double highestVal);
};