#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <ballAngle.h>
#include <motor.h>
#include <lineSensor.h>
#include <compassSensor.h>
#include <Cam.h>
#include <stdlib.h>


BallAngle ballAngle;
Motor motor;
LineSensor lineSensor;
CompassSensor compassSensor;
Cam cam;
int initialOrientation = compassSensor.getOrientation();
int startState = 0;
double camAngle = 0;


void setup()
{

  Serial2.begin(19200);

  // pinMode(10,OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  pinMode(36,INPUT_PULLUP);
}


int tick = 0;
void runRobot()
{
  

  ballAngle.kickButton();

  camAngle = cam.CamAngle();
  
  //lineSensor.GetValues();
  

  
  ballAngle.Process();
  motor.Move(ballAngle.robotAngle, compassSensor.getOrientation(), initialOrientation);
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
  // if (ballAngle.capture == 1)
  // {
  //   int goalOrientation = initialOrientation;
  //   Serial.print("initialOrientation: ");
  //   Serial.println(initialOrientation);
  //   if (camAngle >180)
  //   {
  //     camAngle = camAngle -360;
  //   }
    
  //   goalOrientation += camAngle;
  //   if (goalOrientation <0)
  //   {
  //     goalOrientation+=360;
  //   }
    
  //   Serial.print("goalOrientation: ");
  //   Serial.println(goalOrientation);
    
  //   motor.Move(ballAngle.robotAngle, compassSensor.getOrientation(), goalOrientation);
  // }

  // else
  // {
  //   motor.Move(ballAngle.robotAngle, compassSensor.getOrientation(), initialOrientation);
  // }
  

}

void loop()
{
  delay(1000);
  if(startState == 0)
  {
    int startbutton = digitalRead(36);
    
    if( startbutton == 0)
    {
      startState = 1;
      Serial.println("Started");
    }
    Serial.println("Press Button To start");
  }
  else
  {
    runRobot();
  }
}

