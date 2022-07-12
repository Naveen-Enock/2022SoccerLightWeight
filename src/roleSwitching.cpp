#include <roleSwitching.h>

Switching::Switching()
{
ballDist = 1025;
transmitNum = "";
offenseRole = true;
}

void Switching::proximity()
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

void Switching::sendData(double highestVal, bool robotRole)
{
    Serial8.print(highestVal);
    Serial8.print("|");
    Serial8.print(robotRole);
    Serial8.println("a");
}

void Switching::role(int highestVal) 
{
  Switch = false;
    sendData(highestVal, offenseRole);
    proximity();
    if(xbeeRole == true){
      offenseRole = false;
    }
if(offenseRole == false){
  if(highestVal > 660){
    offenseRole = true;
  }
}
if(offenseRole == true && xbeeRole == true)
{
  Switch = true;
}



}