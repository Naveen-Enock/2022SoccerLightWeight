#include <Cam.h>
#include <cstdlib>
Cam::Cam()
{
 buff = 0;
 buffer = "";
}
double Cam::CamAngle()
{
  // Read the most recent byte

  if (Serial2.available() > 0)
  {
    
    for (int i = 0; i < Serial2.available(); i++)
    {
      char read = Serial2.read();
      if (read == 'a')
      {
        buff = strtod(buffer.c_str(), NULL);
        //Serial.println(buff);
        
        buffer = "";
        return buff;
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