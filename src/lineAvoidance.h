#include <lineSensor.h>

class LineAvoidance {
  public: 
     LineAvoidance();  
     bool lineSwitch;
      void Process(bool ball);
      int lowestval;
      int highestval;
      int sensorAngle;
      int anglebisc;
      double chord;
      double chordlength;
      double lineFR;
      double lineFL;
      double lineRR;
      double lineRL;
      int initialAngle;
      int currentAngle;
      int angleDiff;
      int lineAngle;
      bool linepresent = false;
      void angle();

        

    private:
    int *lineValues;
    int *sensorAngles;
    LineSensor lineSensor;
    
    void Chord();
    void Power(bool ball);
    int initialWait;
};