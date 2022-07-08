#include <calibration.h>

Calibration::Calibration(){
  calVal = new int[24];
  for (int i = 0; i < 24; i++)
  {
      calVal[i] = -1;
  }
    
}

void Calibration::calibrate(int *lineVal){


for (int i = 0; i < 24; i++)
{
if(calVal[i]<lineVal[i])
{
    calVal[i] = lineVal[i];    
}

}
}