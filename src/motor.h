#include <Arduino.h>

class Motor
{

public:
    Motor();
    void Move(double robotAngle);

private:
    int speedRR;
    int speedFR;
    int speedFL;
    int speedRL;
    int controlRR;
    int controlFR;
    int controlFL;
    int controlRL;
};