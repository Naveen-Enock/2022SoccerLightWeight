#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <iostream>

class Switching 
{
public:
Switching();
double ballDist;
void role(int highestVal, bool findLine);
bool offenseRole;
void proximity();
int xbeeRole;
void sendData(double highestVal, int robotRole);
bool Switch;
private:


char transmit;
std::string transmitNum;
int buttonState;

};