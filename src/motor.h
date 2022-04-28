#include <Arduino.h>
#include <trig.h>


class Motor
{

public:
    Motor();
    void Move(bool ballpresent, double robotAngle,double orientation, double initialOrientation, double lineFR, double lineRR, double lineRL, double lineFL);
    double correction;
    


private:
    int speedRR;
    int speedFR;
    int speedFL;
    int speedRL;
    int controlRR;
    int controlFR;
    int controlFL;
    int controlRL;
    void GetMotorDirectionAndSpeed(int &direction, double &power,double maxValue );
    void GetMotorDirectionAndRealSpeed(int &direction, double &power,double maxValue );
    void Orientation(double orientation, double initialOrientation);
};