#include <lineSensor.h>

class LineAvoidance {
  public: 
     LineAvoidance();  
      void Process();
        

    private:
    int *lineValues;
    LineSensor lineSensor;
         
};