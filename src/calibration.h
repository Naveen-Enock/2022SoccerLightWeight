#include <lineSensor.h>



class Calibration{

public:
Calibration();
void calibrate(int *calValues);
int *calVal;


private:
int *lineValues;
//LineSensor calSensor;
};