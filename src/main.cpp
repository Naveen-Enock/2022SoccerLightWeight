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
#include <Xbee.h>

BallAngle ballAngle;
Motor motor;
CompassSensor compassSensor;
//LineSensor lineSensor;
Cam cam;
Defense defense;
Goal goal;
LineAvoidance lineAvoidance;
Xbee xbee;
int initialOrientation = -1;

double camAngle = -1;
int buttonstate = -1;
int startstate = -1;
int delayTick = -1;

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
    cam.camSend("1");
    ballAngle.Process();
    xbee.role(ballAngle.realhighestVal);
    lineAvoidance.Process(ballAngle.ballpresent);
    defense.defense(lineAvoidance.anglebisc, ballAngle.ballAngle, lineAvoidance.linepresent, lineAvoidance.lineSwitch);
    motor.Move(ballAngle.ballpresent, defense.defenseAngle, compassSensor.getOrientation(), initialOrientation, lineAvoidance.lineFR, lineAvoidance.lineRR, lineAvoidance.lineRL, lineAvoidance.lineFL);
  }
  else
  {
    cam.camSend("1");
    cam.camAverage();
    //ballAngle.kickButton();
    ballAngle.Intake();
    ballAngle.Process();
    xbee.role(ballAngle.realhighestVal);
    lineAvoidance.Process(ballAngle.ballpresent);
    goal.Kick(cam.dist, ballAngle.capture, motor.correction);
    if (cam.dist < 150)
    {
      goal.Process(initialOrientation, cam.buff);
      motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation(), goal.goalAngle, lineAvoidance.lineFR, lineAvoidance.lineRR, lineAvoidance.lineRL, lineAvoidance.lineFL);
    }
    else
    {
      motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation(), initialOrientation, lineAvoidance.lineFR, lineAvoidance.lineRR, lineAvoidance.lineRL, lineAvoidance.lineFL);
    }
  }
}

void loop()
{
  //delay(100);

  if (delayTick < 20)
  {
    delayTick = delayTick + 1;
  }

  else
  {
    if (buttonstate == -1)
    {
      startstate = digitalRead(36);
      if (startstate == 0)
      {
        buttonstate = startstate + 2;
      }

      
      Serial.println("press button to start");
      
    }

    else if (buttonstate == 2)
    {
      initialOrientation = compassSensor.getOrientation();
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
      digitalWrite(28, HIGH);
      digitalWrite(33, HIGH);
      analogWrite(29, 0);
      analogWrite(15, 0);
      digitalWrite(6, HIGH);
      digitalWrite(4, HIGH);
      analogWrite(5, 0);
      analogWrite(3, 0);
      buttonstate = -1;
    }
  }
}