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

BallAngle ballAngle;
Motor motor;
CompassSensor compassSensor;
//LineSensor lineSensor;
Cam cam;
Goal goal;
LineAvoidance lineAvoidance;
int initialOrientation = -1;

double camAngle = -1;
int buttonstate = -1;
int startstate = -1;
int tick = -1;

void setup()
{

  Serial2.begin(19200);

  // pinMode(10,OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(36, INPUT_PULLUP);
}
void runRobot()
{

  cam.camAverage();
  ballAngle.kickButton();
  ballAngle.Intake();
  ballAngle.Process();
  lineAvoidance.Process(ballAngle.ballpresent);
  goal.Kick(cam.dist, ballAngle.capture, motor.correction);
  if (cam.dist < 150)
  {
    goal.Process(initialOrientation, cam.buff);
    motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation() , goal.goalAngle, lineAvoidance.lineFR,lineAvoidance.lineRR,lineAvoidance.lineRL,lineAvoidance.lineFL);
    tick = 1;
  }
  else if (tick>0 && tick <= 2000)
    {
    goal.Process(initialOrientation, cam.buff);
    motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation() , goal.goalAngle, lineAvoidance.lineFR,lineAvoidance.lineRR,lineAvoidance.lineRL,lineAvoidance.lineFL);

    tick = tick+1;
    }

  if (tick>2000 || (cam.dist >= 150 && tick == -1))
  {
  motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation() , initialOrientation, lineAvoidance.lineFR,lineAvoidance.lineRR,lineAvoidance.lineRL,lineAvoidance.lineFL);
  tick = -1;
  }

}

void loop()
{
  delayMicroseconds(100);
  if (buttonstate == -1)
  {
    startstate = digitalRead(36);
    if (startstate == 0)
    {
      buttonstate = startstate +2;
    }
    
    //LineSensor lineSensor;
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
    buttonstate = digitalRead(36);
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
