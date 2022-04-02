#include <ballSensor.h>
#include <trig.h>
class BallAngle {

    public: 
        BallAngle();
        void Process();
        double ballAngle;
        double lowestValue;
        double robotAngle;

    private:
        BallSensor ballSensor;
        int *sensorValues;
        void CalculateRobotAngle(); 
};