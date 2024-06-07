/*
  Author  : Andrea Lombardo
  Site    : https://www.lombardoandrea.com
  Source  : https://github.com/AndreaLombardo/L298N/

  Here you can see how to work in a common configuration.

  L298NX2 is not a new version of module or IC,
  but it stands for a double implementation of L298N library.

  With L298NX2 is possible to initialize two motors at once.

  Speed range go from 0 to 255, default is 100.
  Use setSpeed(speed) to change speed for both motors,
  setSpeedA(speed) or setSpeedB(speed) for individual changes.

  Sometimes at lower speed motors seems not running.
  It's normal, may depends by motor and power supply.

  Wiring schema in file "L298NX2 - Schema_with_EN_pin.png"
*/

// Include the (new) library
#include <L298NX2.h>

// Pin definition
const unsigned int EN_A = 7;
const unsigned int EN_B = 6;

const unsigned int IN2_B = 5;
const unsigned int IN1_B = 4;
const unsigned int IN2_A = 1;
const unsigned int IN1_A = 0;

// Initialize both motors
L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

void setup()
{
  pinMode(28, OUTPUT); 
  pinMode(29, OUTPUT);    
}
void loop()
{
  
  motors.setSpeedA(255);
  motors.setSpeedB(255);
 // Tell motor A to go back (may depend by your wiring)
  motors.runA(L298N::FORWARD);
  motors.runB(L298N::FORWARD);
  digitalWrite(28,HIGH);
  digitalWrite(29,LOW);
  delay(1000);
  motors.runA(L298N::STOP);
  motors.runB(L298N::STOP);
  digitalWrite(28,LOW);
  digitalWrite(29,LOW);
  delay(500);
  
  motors.setSpeedA(200);
  motors.setSpeedB(100);
 // Tell motor A to go back (may depend by your wiring)
  motors.runA(L298N::BACKWARD);
  motors.runB(L298N::BACKWARD);
  digitalWrite(28,LOW);
  digitalWrite(29,HIGH);
  delay(1000);
  motors.runA(L298N::STOP);
  motors.runB(L298N::STOP);
  digitalWrite(28,LOW);
  digitalWrite(29,LOW);
  delay(500);
  

  
  motors.setSpeedA(100);
  motors.setSpeedB(200);
 // Tell motor A to go back (may depend by your wiring)
  motors.runA(L298N::BACKWARD);
  motors.runB(L298N::BACKWARD);
  digitalWrite(28,LOW);
  digitalWrite(29,HIGH);
  delay(1000);
  motors.runA(L298N::STOP);
  motors.runB(L298N::STOP);
  digitalWrite(28,LOW);
  digitalWrite(29,LOW);
  delay(500);
}

/*
 // Change individual speeds
  motors.setSpeedA(255);
  motors.setSpeedB(255);
  
  
 // Tell motor A to go back (may depend by your wiring)
  motors.runA(L298N::FORWARD);
  motors.runB(L298N::FORWARD);
  digitalWrite(28,HIGH);
  digitalWrite(29,LOW);
  printSomeInfo(); 
  delay(1000);
 
  Print some informations in Serial Monitor
*/
