#include <Cam.h>
#include <cstdlib>
Cam::Cam()
{
 buff = 0;
 dist = 0;
 buffer = "";
}
double Cam::CamCalc()
{
  // Read the most recent byte

  if (Serial2.available() > 0)
  {
    
    for (int i = 0; i < Serial2.available(); i++)
    {
      char read = Serial2.read();
      if (read == 'a')
      {
        dist = strtod(buffer.c_str(), NULL);
        buffer = "";
      }
      
      else if (read == '|')
      {
        buff = strtod(buffer.c_str(), NULL);
        //Serial.println(buff);
        
        buffer = "";
      }
      else
      {

        buffer += read;
        //Serial.println(atof(buffer.c_str()));
      }
    }
  }
  return 0;
};


