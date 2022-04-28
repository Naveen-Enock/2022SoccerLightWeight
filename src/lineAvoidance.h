#include <lineSensor.h>

class LineAvoidance {
  public: 
     LineAvoidance();  
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

        

    private:
    int *lineValues;
    int *sensorAngles;
    LineSensor lineSensor;
    void angle();
    void Chord();
    void Power(bool ball);
};