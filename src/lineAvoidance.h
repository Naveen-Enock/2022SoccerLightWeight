#include <lineSensor.h>
#include <calibration.h>

class LineAvoidance {
  public: 
     LineAvoidance();  
     bool lineSwitch;
      void Process(bool ball, int *calibrateVal);
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
      void angle(int *calibrateVal);
      
      bool projectionState;
      int projectionAngle;
      bool outOfBounds;
      int *lineValues;
       //LineSensor lineSensor;

        

    private:
    
    int *sensorAngles;
    int *calVal;
   
    
    
    void Chord();
    void Power(bool ball);
    int initialWait;
};