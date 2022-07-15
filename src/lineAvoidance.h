#include <lineSensor.h>

class LineAvoidance {
  public: 
     LineAvoidance();  
     bool lineSwitch;
      void Process(bool ball, int *calibrateVal, int *lineVal, int *sensorVal, double chordThreshold, double *sinVal, double *cosVal);
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
      void angle(int *calibrateVal, int *lineVal, int *sensorVal, double *sinVal, double *cosVal);
      
      bool projectionState;
      int projectionAngle;
      bool outOfBounds;
      
      

        

    private:
    
    int *sensorAngles;
    int *lineValues;
     double *cosValues; 
    double *sinValues;
   bool negativeLow;
   double *dotProduct;
    double dot;
    double lowestDot;
       int firstAngle;
    int secondAngle;
    
    void Chord();
    void Power(bool ball);
    int initialWait;
    int lineBisc;
};