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
        int buttonState = 1;
        void kickButton();
        

    private:
        BallSensor ballSensor;
        int *sensorValues;
        void CalculateRobotAngle(); 
        
};