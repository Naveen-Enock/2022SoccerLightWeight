class Goal
{
public:
Goal();
void Process(int initialOrientation, double goalOrientation);
double goalAngle;
void Kick(double goalDist,bool capture, double correction);
int kickTimer;
int kickActivate;
int kickWait;
private:

};