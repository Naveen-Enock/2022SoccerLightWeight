#include <Arduino.h>
#include <trig.h>


class Motor
{

public:
    Motor();
    void Move(bool ballpresent, double robotAngle,double orientation, double initialOrientation, double lineFR, double lineRR, double lineRL, double lineFL, bool projectionState, int projectionAngle, bool defenseStop);
    double correction;
    double robotX;
    double robotY;
    double lineX;
    double lineY;
    double dotProduct;
    double denominator;
    double projectionX;
    double projectionY;
    
    


private:
    double maxval;
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
    void LineFollow(double &robotAngle, int projectionAngle);
};