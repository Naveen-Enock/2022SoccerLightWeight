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

  if (xbee.offenseRole == false)
  {
 

    cam.camAverage();

    ballAngle.Process();
    xbee.role(ballAngle.xbeeHighVal);
    lineAvoidance.Process(ballAngle.ballpresent, calibration.calVal, lineSensor.GetValues(), lineSensor.LineAngle());
    defense.defense(lineAvoidance.projectionAngle, ballAngle.ballAngle,cam.buff,lineAvoidance.linepresent, initialOrientation);
    motor.Move(ballAngle.ballpresent, defense.defenseAngle, compassSensor.getOrientation(), initialOrientation, lineAvoidance.lineFR, lineAvoidance.lineRR, lineAvoidance.lineRL, lineAvoidance.lineFL,lineAvoidance.projectionState,lineAvoidance.projectionAngle, defense.stop);
  }
  else
  {

    cam.camAverage();
    //ballAngle.kickButton();
    ballAngle.Intake();
    ballAngle.Process();
    xbee.role(ballAngle.xbeeHighVal);
    lineAvoidance.Process(ballAngle.ballpresent, calibration.calVal, lineSensor.GetValues(), lineSensor.LineAngle());
    //goal.Kick(cam.dist, ballAngle.capture, motor.correction);
    defense.stop = false;
    Serial.println(cam.buff2);
   goal.Process(compassSensor.getOrientation(), cam.buff2, initialOrientation);
      
    motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation(), goal.goalAngle , lineAvoidance.lineFR, lineAvoidance.lineRR, lineAvoidance.lineRL, lineAvoidance.lineFL,lineAvoidance.projectionState,lineAvoidance.projectionAngle,defense.stop);

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
   

    }

    else if (buttonstate == 2)
    {
      initialOrientation = compassSensor.getOrientation();
      for(int i = 0; i<24;i++)
      {
        calibration.calVal[i]+=10;
      }
      buttonstate = 1;
    }

    else if (buttonstate == 1)
    {
      runRobot();

      
      buttonstate = digitalRead(9);
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
      buttonstate = -1;
    }
  }
}