#include <lineSensor.h>

class LineAvoidance {
  public: 
     LineAvoidance();  
     bool lineSwitch;
      void Process(bool ball, int *calibrateVal, int *lineVal, int *sensorVal, double chordThreshold);
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
      void angle(int *calibrateVal, int *lineVal, int *sensorVal);
      
      bool projectionState;
      int projectionAngle;
      bool outOfBounds;
      
      

        

    private:
    
    int *sensorAngles;
    int *lineValues;
   
    
    
    void Chord();
    void Power(bool ball);
    int initialWait;
};