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
      if(transmit == '|')
      {
        ballDist = strtod(transmitNum.c_str(), NULL);
        Serial.println(ballDist);
        transmitNum = "";
      }
      else if (transmit == 'a')
      {
        xbeeRole = strtod(transmitNum.c_str(), NULL);
        Serial.println(xbeeRole);
        transmitNum = "";
      }


      else
      {

        transmitNum += transmit;
        
      }
    }
  }
 
}

void Xbee::sendData(double highestVal, bool robotRole)
{
    Serial8.print(highestVal);
    Serial8.print("|");
    Serial8.print(robotRole);
    Serial8.println("a");
}

void Xbee::role(int highestVal) 
{
    sendData(highestVal, offenseRole);
    proximity();
    offenseRole = true;
if(highestVal>ballDist)
{
offenseRole = true;
}
else if(ballDist>highestVal)
{
  offenseRole = false;
}


}