#include <calibration.h>

Calibration::Calibration(){
  calVal = new int[24];
  for (int i = 0; i < 24; i++)
  {
      calVal[i] = 1024;
  }
    
}

void Calibration::calibrate(int *calValues){
lineValues = calValues;

for (int i = 0; i < 24; i++)
{
if(lineValues[i]<calVal[i])
{
    calVal[i] = lineValues[i];    
}

}
}