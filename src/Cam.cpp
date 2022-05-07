#include <Cam.h>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
Cam::Cam()
{
  buff = 0;
  dist = 0;
  buffer = "";
  angleAverage = new int[10];
  distAverage = new int[10];
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

double Cam::camAverage()
{

  for (int i = 0; i < 10; i++)
  {
    CamCalc();
    angleAverage[i] = buff;
    distAverage[i] = dist;
  }
  sort(angleAverage, angleAverage + 10);
  buff = (angleAverage[4] + angleAverage[5]) / 2.0;
  Serial.print("goalAngle : ");
  Serial.println(buff);
  sort(distAverage, distAverage + 10);
  dist = (distAverage[4] + distAverage[5]) / 2.0;
  Serial.print("dist : ");
  Serial.println(dist);
};
