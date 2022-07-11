class Goal
{
public:
Goal();
void Process(int Orientation, double goalOrientation, int initialOrientation);
double goalAngle;
void Kick(double goalDist,bool capture, double correction);

private:
int kickTimer;
int kickActivate;
int kickWait;
int goalInitiate;
double realAngle;
double goalDiff;
int placeHolder;
};