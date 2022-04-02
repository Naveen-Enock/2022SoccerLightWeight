#include <ballSensor.h>

class BallAngle {

    public: 
        BallAngle();
        double GetAngle();

    private:
        BallSensor ballSensor; 
};