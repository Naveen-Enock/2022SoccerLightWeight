#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <ballAngle.h>
#include <motor.h>
#include <Goal.h>
#include <compassSensor.h>
#include <Cam.h>
#include <lineAvoidance.h>
#include <stdlib.h>
#include <Defense.h>
#include <roleSwitching.h>
#include <calibration.h>


BallAngle ballAngle;
Motor motor;
CompassSensor compassSensor;
LineSensor lineSensor;
Cam cam;
Defense defense;
Goal goal;
LineAvoidance lineAvoidance;
Switching xbee;
Calibration calibration;

int initialOrientation = -1;


double camAngle = -1;
int buttonstate = -1;
int startstate = -1;
int delayTick = -1;
int calState = -1;

void setup()
{
initialOrientation = compassSensor.getOrientation();
  Serial2.begin(19200);
  Serial8.begin(9600);

  // pinMode(10,OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(36, INPUT_PULLUP);
}
void runRobot()
{
   ballAngle.Process();
  xbee.role(ballAngle.xbeeHighVal, defense.findLine);
        

  if (xbee.offenseRole == false)
  {
    

    cam.camAverage();

   
    
    lineAvoidance.Process(ballAngle.ballpresent, calibration.calVal, lineSensor.GetValues(), lineSensor.LineAngle(),0.7, lineSensor.GetCosValues(), lineSensor.GetSinValues());
    defense.defense(xbee.Switch, ballAngle.ballAngle,cam.buff,lineAvoidance.linepresent, initialOrientation);
    motor.Move(ballAngle.ballpresent, defense.defenseAngle, compassSensor.getOrientation(), initialOrientation, lineAvoidance.lineFR, lineAvoidance.lineRR, lineAvoidance.lineRL, lineAvoidance.lineFL,lineAvoidance.projectionState,lineAvoidance.projectionAngle, defense.stop);
  }
  else
  {

    cam.camAverage();
    //ballAngle.kickButton();
    ballAngle.Intake();
  
   
    lineAvoidance.Process(ballAngle.ballpresent, calibration.calVal, lineSensor.GetValues(), lineSensor.LineAngle(), 0.2, lineSensor.GetCosValues(), lineSensor.GetSinValues());
    goal.Kick(cam.dist, ballAngle.capture, motor.correction);
    defense.stop = false;
    if(ballAngle.ballAngle <45 || ballAngle.ballAngle > 315){
   goal.Process(compassSensor.getOrientation(), cam.buff2, initialOrientation);
      ballAngle.CalculateRobotAngle(cam.buff);
    motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation(), goal.goalAngle , lineAvoidance.lineFR, lineAvoidance.lineRR, lineAvoidance.lineRL, lineAvoidance.lineFL,lineAvoidance.projectionState,lineAvoidance.projectionAngle,defense.stop);
    }
    else{
     ballAngle.CalculateRobotAngle(-5);
      motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation(), initialOrientation , lineAvoidance.lineFR, lineAvoidance.lineRR, lineAvoidance.lineRL, lineAvoidance.lineFL,lineAvoidance.projectionState,lineAvoidance.projectionAngle,defense.stop);
    }
  }
}

void loop()
{
//delay(1000);

  if (delayTick < 2)
  {
    delayTick = delayTick + 1;
  }

  else
  {
    if (buttonstate == -1)
    {
      startstate = digitalRead(36);
      calState = digitalRead(9);
      if (startstate == 0)
      {
        buttonstate = 2;
      }
      if(calState == 0){
        calibration.calibrate(lineSensor.GetValues());
      }
      
      Serial.println("press button to start");
      //ballAngle.kickButton();
   

    }

    else if (buttonstate == 2)
    {
      
      for(int i = 0; i<24;i++)
      {
        calibration.calVal[i]+=50;
      }
      buttonstate = 1;
    }

    else if (buttonstate == 1)
    {

      
      runRobot();
      //buttonstate = digitalRead(9);
    }

    else if (buttonstate == 0)
    {
      Serial.println("yo");
      digitalWrite(4, LOW);
      digitalWrite(33, LOW);
      analogWrite(29, 0);
      analogWrite(28, 0);
      digitalWrite(6, LOW);
      digitalWrite(4, LOW);
      analogWrite(5, 0);
      analogWrite(3, 0);
            for(int i = 0; i<24;i++)
      {
        calibration.calVal[i] = -1;
      }
      buttonstate = -1;
    }
  }
}