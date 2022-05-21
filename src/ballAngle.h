#include <ballSensor.h>
#include <trig.h>
class BallAngle {

    public: 
        BallAngle();
        void Process();
        double ballAngle;
        double highestValue;
        double robotAngle;
        void Intake();
        bool capture = false;
        int kickState = 1;
        void kickButton();
        bool ballpresent = false;
        int realhighestVal;
        

    private:
        BallSensor ballSensor;
        int *sensorValues;
        void CalculateRobotAngle(); 
        
};