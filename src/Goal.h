class Goal
{
public:
Goal();
void Process(int initialOrientation, double goalOrientation, bool offense);
double goalAngle;
void Kick(double goalDist,bool capture, double correction);

private:
int kickTimer;
int kickActivate;
int kickWait;
int goalInitiate;
double realAngle;
double goalDiff;
};