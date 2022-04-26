#include <ballSensor.h>
#include <trig.h>
class BallAngle {

    public: 
        BallAngle();
        void Process();
        double ballAngle;
        double highestValue;
        double robotAngle;
        int Intake();
        bool capture = false;
        int kickState = 1;
        void kickButton();
        bool ballpresent = false;
        

    private:
        BallSensor ballSensor;
        int *sensorValues;
        void CalculateRobotAngle(); 
        
};