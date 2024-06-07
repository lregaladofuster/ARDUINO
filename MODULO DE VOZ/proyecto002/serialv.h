
#include "configproy.h"

extern void serialEventRun(void) __attribute__((weak));
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void config_usart(){
  Serial.begin(9600,SERIAL_8N1);
  Serial1.begin(9600,SERIAL_8N1);
  Serial2.begin(9600,SERIAL_8N1);
  Serial3.begin(9600,SERIAL_8N1);
  inputString.reserve(30);
}
void serialEventRun(void) {
  if (Serial.available()) serialEvent();
  if (Serial1.available()) serialEvent1();
  if (Serial2.available()) serialEvent2();
  if (Serial3.available()) serialEvent3();
}
void serialEvent() {
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
}
void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
void serialEvent2() {
  while (Serial2.available()) {
    // get the new byte:
    char inChar = (char)Serial2.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
void serialEvent3() {
  while (Serial3.available()) {
    // get the new byte:
    char inChar = (char)Serial3.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void recepcion(void){
  if (stringComplete) {
    Serial.print(inputString);
    mov=0;//hace de default
    if(inputString=="00\n"){mov=0;}
    if(inputString=="01\n"){mov=1;}
    if(inputString=="02\n"){mov=2;}
    if(inputString=="03\n"){mov=3;}
    if(inputString=="04\n"){mov=4;}
    Serial.println(mov,10);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void config_voz(){
  do{
    Serial1.write((byte)0xAA);
    Serial1.write((byte)0x06);
    Serial1.write((byte)0x30);
    Serial1.write((byte)0x00);//puede ser interpretado como un puntero//NULL
    Serial1.write((byte)0x01);
    Serial1.write((byte)0x02);
    Serial1.write((byte)0x03);
    Serial1.write((byte)0x0A);
    delay(500);
    if (stringComplete) {
      Serial.print(inputString);
      // clear the string:
      inputString = "";
    }
  }while(stringComplete==false);
  stringComplete=false;
}
