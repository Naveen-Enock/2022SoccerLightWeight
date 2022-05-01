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

void setup()
{

  Serial2.begin(19200);

  // pinMode(10,OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(36, INPUT_PULLUP);
}

int tick = 0;
void runRobot()
{

  ballAngle.kickButton();
  ballAngle.Intake();
  ballAngle.Process();
  lineAvoidance.Process(ballAngle.ballpresent);
  if (ballAngle.capture == true)
  {
    goal.Process(initialOrientation, cam.buff);
    motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation() , goal.goalAngle, lineAvoidance.lineFR,lineAvoidance.lineRR,lineAvoidance.lineRL,lineAvoidance.lineFL);
    goal.Kick(cam.dist);
  }
  else
  {


  motor.Move(ballAngle.ballpresent, ballAngle.robotAngle, compassSensor.getOrientation() , initialOrientation, lineAvoidance.lineFR,lineAvoidance.lineRR,lineAvoidance.lineRL,lineAvoidance.lineFL);
  }
  



  
  // if (ballAngle.Intake() == 1 && tick == 0)
  // {
  //   ballAngle.capture = true;
  //   tick = 1;
  // }

  // else if (tick < 10000 && tick > 0)
  // {
  //   ballAngle.capture = true;
  //   tick +=1;
  // }
  // else
  // {
  //   ballAngle.capture = false;
  //   tick = 0;
  // }
  // Serial.print("Capture : ");
  // Serial.println(ballAngle.capture);
  // Serial.print("cam Angle : ");
  //   Serial.println(camAngle);
  
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
