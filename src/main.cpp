#include <Arduino.h>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <MCP3XXX.h>
#include <ballAngle.h>

int adcpin4 = 23;
int adcpin5 = 22;
int adcpin6 = 21;
int channel = 6;
int value;

MCP3008 adc4;
MCP3008 adc5;
MCP3008 adc6;
int speedRR = 29;
int speedFR = 15;
int SpeedFL = 5;
int speedRL = 3;
int controlRR = 28;
int controlFR = 33;
int ControlFL = 6;
int controlRL = 4;
int buttonState = 0; 
BallAngle ballAngle; 
void forward()
{
  digitalWrite(controlRR, LOW);
  digitalWrite(controlFR, LOW);
  analogWrite(speedRR, 255);
  analogWrite(speedFR, 255);
  digitalWrite(ControlFL, HIGH);
  digitalWrite(controlRL, HIGH);
  analogWrite(SpeedFL, 255);
  analogWrite(speedRL, 255);

}

void backward()
{
  digitalWrite(controlRR, HIGH);
  digitalWrite(controlFR, HIGH);
  analogWrite(speedRR, 255);
  analogWrite(speedFR, 255);
  digitalWrite(ControlFL, LOW);
  digitalWrite(controlRL, LOW);
  analogWrite(SpeedFL, 255);
  analogWrite(speedRL, 255);

}

void right()
{
  digitalWrite(controlRR, LOW);
  digitalWrite(controlFR, HIGH);
  analogWrite(speedRR, 255);
  analogWrite(speedFR, 255);
  digitalWrite(ControlFL, HIGH);
  digitalWrite(controlRL, LOW);
  analogWrite(SpeedFL, 255);
  analogWrite(speedRL, 255);

}

void left()
{
  digitalWrite(controlRR, HIGH);
  digitalWrite(controlFR, LOW);
  analogWrite(speedRR, 255);
  analogWrite(speedFR, 255);
  digitalWrite(ControlFL, LOW);
  digitalWrite(controlRL, HIGH);
  analogWrite(SpeedFL, 255);
  analogWrite(speedRL, 255);

}

void stop()
{
  digitalWrite(controlRR, HIGH);
  digitalWrite(controlFR, LOW);
  analogWrite(speedRR, 0);
  analogWrite(speedFR, 0);
  digitalWrite(ControlFL, LOW);
  digitalWrite(controlRL, HIGH);
  analogWrite(SpeedFL, 0);
  analogWrite(speedRL, 0);

}

void setup() {
  Serial.begin(9600);

  adc4.begin(adcpin4,11,12,13);
  adc5.begin(adcpin5,11,12,13);
  adc6.begin(adcpin6,11,12,13);
  pinMode(speedRR, OUTPUT);
  pinMode(speedRL, OUTPUT);
  pinMode(controlRR, OUTPUT);
  pinMode(controlRL,OUTPUT);
  pinMode(controlFR,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,INPUT_PULLUP);
  pinMode(14,INPUT);
  
 
  
}



void loop() {

  Serial.println(ballAngle.GetAngle());
  delay(500);
  // forward();
  // delay(1000);
  // digitalWrite(controlRR, LOW);
  // digitalWrite(controlFR, LOW);
  // analogWrite(speedRR, 255);
  // analogWrite(speedFR, 210);
  // digitalWrite(ControlFL, HIGH);
  // digitalWrite(controlRL, HIGH);
  // analogWrite(SpeedFL, 255);
  // analogWrite(speedRL, 210);
  // delay(1000);
  // digitalWrite(controlRR, LOW);
  // digitalWrite(controlFR, LOW);
  // analogWrite(speedRR, 255);
  // analogWrite(speedFR, 190);
  // digitalWrite(ControlFL, HIGH);
  // digitalWrite(controlRL, HIGH);
  // analogWrite(SpeedFL, 255);
  // analogWrite(speedRL, 190);
  // delay(1000);
  // digitalWrite(controlRR, LOW);
  // digitalWrite(controlFR, LOW);
  // analogWrite(speedRR, 255);
  // analogWrite(speedFR, 0);
  // digitalWrite(ControlFL, HIGH);
  // digitalWrite(controlRL, HIGH);
  // analogWrite(SpeedFL, 255);
  // analogWrite(speedRL, 0);
  // delay(1000);
  // stop();
  // delay(10000);

  // digitalWrite(controlFR, LOW);
  // delay(2000);
  // digitalWrite(controlFR, HIGH);
  // delay(2000);
// for(int i = 0 ; i < 48 ; i++)
// {
//   int adcNumber = (i / 8) + 1;
//   int channel = i % 8;
//   int val = 0;

//   switch (adcNumber)
//   {
//     case 1:
//       val = adc1.analogRead(channel);
//       break;
//     case 2:
//       val = adc2.analogRead(channel);
//       break;
//     case 3:
//       val = adc3.analogRead(channel);
//       break;
//       case 4:
//       val = adc4.analogRead(channel);
//       break;
//     case 5:
//       val = adc5.analogRead(channel);
//       break;
//     case 6:
//       val = adc6.analogRead(channel);
//       break;
    
//     default:
//       break;
//   }
  
//   Serial.print("Pin : ");
//   Serial.print(i+1);
//   Serial.print(" ADC : ");
//   Serial.print(adcNumber);
//   Serial.print(" Channel : ");
//   Serial.print(channel);
//   Serial.print(" val : ");
//   Serial.println(val);
// }


// // delay(1000);
buttonState = digitalRead(9);
if (buttonState == LOW){
digitalWrite(10, HIGH);
}
else {
  digitalWrite(10, LOW);
}
// value = analogRead(14);
// Serial.println(value);
// delay(500);

}