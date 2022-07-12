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
  angleAverage = new int[20];
  distAverage = new int[20];
  angle2Average = new int[20];
  dist2Average = new int[20];
  dataNum = 0;
}
double Cam::CamCalc()
{
  // Read the most recent byte

  if (Serial2.available() > 0)
  {

    for (int i = 0; i < Serial2.available(); i++)
    {
      read = Serial2.read();
      if (read == 'a')
      {
        dist2 = strtod(buffer.c_str(), NULL);
        dataNum = 0;
        buffer = "";
      }

      else if (read == '|'&& dataNum == 0)
      {
        buff = strtod(buffer.c_str(), NULL);
        dataNum++;
        buffer = "";
      }
      else if (read == '|'&& dataNum == 1)
      {
        dist = strtod(buffer.c_str(), NULL);
        dataNum++;
        buffer = "";
      }
      else if (read == '|'&& dataNum == 2)
      {
        buff2 = strtod(buffer.c_str(), NULL);
        dataNum++;
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

  for (int i = 0; i < 20; i++)
  {
    CamCalc();
    angleAverage[i] = buff;
    distAverage[i] = dist;
    dist2Average[i] = dist2;
    angle2Average[i] = buff2;
  }
  
  sort(angleAverage, angleAverage + 20);
  buff = (angleAverage[9] + angleAverage[10]) / 2.0;
  Serial.print("YellowGoal : ");
  Serial.println(buff);
  sort(angle2Average, angle2Average + 20);
  buff2 = (angle2Average[9] + angle2Average[10]) / 2.0;
  Serial.print("BlueGoal : ");
  Serial.println(buff2);
  sort(distAverage, distAverage + 20);
  dist = (distAverage[9] + distAverage[10]) / 2.0;
  Serial.print("YelowDist : ");
  Serial.println(dist);
  sort(dist2Average, dist2Average + 20);
  dist2 = (dist2Average[9] + dist2Average[10]) / 2.0;
  Serial.print("BlueDist : ");
  Serial.println(dist2);
};

double Cam::camSend(String role)
{
  Serial2.println(role);
}
