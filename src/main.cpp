#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <ballAngle.h>
#include <motor.h>
#include <lineSensor.h>
#include <compassSensor.h>





int buttonState = 0; 
BallAngle ballAngle; 
Motor motor;
LineSensor lineSensor;
CompassSensor compassSensor;

void setup() {
  Serial.begin(9600);



  // pinMode(10,OUTPUT);
  // pinMode(9,INPUT_PULLUP);
  // pinMode(14,INPUT);
   
}

void loop() {
 int *values = lineSensor.GetValues(); 
  ballAngle.Process();
   motor.Move(ballAngle.robotAngle,compassSensor.getOrientation());
delay(1);
}






// #define BNO055_SAMPLERATE_DELAY_MS (100)










// void setup(void)
// {
//   Serial.begin(115200);
//   Serial.println("Orientation Sensor Test"); Serial.println("");

//   /* Initialise the sensor */
  

//   delay(1000);

//   /* Display some basic information on this sensor */
//   displaySensorDetails();

//   /* Optional: Display current status */
//   displaySensorStatus();

 
// }


// void loop(void)
// {






//   displayCalStatus();


//   Serial.println("");


//   delay(BNO055_SAMPLERATE_DELAY_MS);
// }