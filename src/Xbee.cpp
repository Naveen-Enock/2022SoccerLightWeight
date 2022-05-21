#include <Xbee.h>

Xbee::Xbee()
{
ballDist = 1025;
transmitNum = "";
offenseRole = false;
}

void Xbee::proximity()
{
if (Serial8.available() > 0)
  {

    for (int i = 0; i < Serial8.available(); i++)
    {
      transmit = Serial8.read();
      if (transmit == 'a')
      {
        ballDist = strtod(transmitNum.c_str(), NULL);
        Serial.println(ballDist);
        transmitNum = "";
      }


      else
      {

        transmitNum += transmit;
        
      }
    }
  }
 
}

void Xbee::sendData(double highestVal)
{
    Serial8.print(highestVal);
    Serial8.println("a");
}

void Xbee::role(double highestVal) 
{
    sendData(highestVal);
    proximity();
if(highestVal>ballDist)
{
offenseRole = true;
}
else if(ballDist>highestVal)
{
    offenseRole = false;
}
}