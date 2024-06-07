/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent
*/
#include <Wire.h>
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool stringComplete1 = false;  // whether the string is complete
bool stringComplete2 = false;
bool stringComplete3 = false;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.setTimeout(50);
  Serial1.begin(9600);
  Serial1.setTimeout(50);
  Serial2.begin(9600);
  Serial2.setTimeout(50);
  Serial3.begin(9600);
  Serial3.setTimeout(50);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  Serial.println("hola");
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    Serial1.println(inputString);
    Serial2.println(inputString);
    Serial3.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  if (stringComplete1) {
    Serial.print(inputString);
    //Serial1.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete1 = false;
  }
  if (stringComplete2) {
    Serial.print(inputString);
    Serial2.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete2 = false;
  }
  if (stringComplete3) {
    Serial.print(inputString);
    Serial3.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete3 = false;
  }
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete1 = true;
    }
  }
  while (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete2 = true;
    }
  }
  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete3 = true;
    }
  }
  
  
}
