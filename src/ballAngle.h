#include <ballSensor.h>
#include <trig.h>
class BallAngle {

    public: 
        BallAngle();
        void Process();
        double ballAngle;
        double highestValue;
        double robotAngle;

    private:
        BallSensor ballSensor;
        int *sensorValues;
        void CalculateRobotAngle(); 
};