////////////////////////////
#include <string>
#include <cstring>
///////////////
#define SYSRESETREQ    (1<<2)
#define VECTKEY        (0x05fa0000UL)
#define VECTKEY_MASK   (0x0000ffffUL)
#define AIRCR          (*(uint32_t*)0xe000ed0cUL) // fixed arch-defined address
#define REQUEST_EXTERNAL_RESET (AIRCR=(AIRCR&VECTKEY_MASK)|VECTKEY|SYSRESETREQ)
////////////////////
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool stringComplete1 = false;  // whether the string is complete
bool stringComplete2 = false;
bool stringComplete3 = false;

void config_usart(){
  // initialize serial:
  Serial.begin(9600);
  Serial.setTimeout(50);
  Serial1.begin(9600);
  Serial1.setTimeout(50);
  Serial2.begin(9600);
  Serial2.setTimeout(50);
  Serial3.begin(9600);
  Serial3.setTimeout(50);
  inputString.reserve(30);
  Serial.println ("bienvenido");
  Serial2.println("bienvenido");
  Serial3.println("bienvenido");
return;}

void config_voz(){
    Serial1.write((byte)0xAA);
    Serial1.write((byte)0x08);
    Serial1.write((byte)0x30);
    Serial1.write((byte)0x00);//puede ser interpretado como un puntero//NULL
    Serial1.write((byte)0x01);
    Serial1.write((byte)0x02);
    Serial1.write((byte)0x03);
    Serial1.write((byte)0x04);
    Serial1.write((byte)0x05);
    Serial1.write((byte)0x0A);
    inputString = "";        // a String to hold incoming data
    stringComplete  = false; // whether the string is complete
    stringComplete1 = false; // whether the string is complete
    stringComplete2 = false;
    stringComplete3 = false;
return;}

void readSerial(void) {
  while (Serial.available()>0) {
    char inChar = (char)Serial.read();
    if(inChar>0x29 & inChar<0x3A){inputString += inChar;}
    if(inChar == '\n') {stringComplete = true;}
  }
  while (Serial1.available()>0) {
    char inChar = (char)Serial1.read();
    if(inChar>0x29 & inChar<0x3A){inputString += inChar;}
    if(inChar == '\n') {stringComplete1= true;}
  }
  while (Serial2.available()>0) {
    char inChar = (char)Serial2.read();
    if(inChar>0x29 & inChar<0x3A){inputString += inChar;}
    if(inChar == '\n') {stringComplete2= true;}
  }
  while (Serial3.available()>0) {
    char inChar = (char)Serial3.read();
    if(inChar>0x29 & inChar<0x3A){inputString += inChar;}
    if(inChar == '\n') {stringComplete3= true;}
  }
return;}

char comparar_mensaje(){
  static char indiceC=0;
  if(inputString=="00"){indiceC=0;}
  if(inputString=="01"){indiceC=1;}
  if(inputString=="02"){indiceC=2;}
  if(inputString=="03"){indiceC=3;}
  if(inputString=="04"){indiceC=4;}
  if(inputString=="0" ){indiceC=9;}//modulo de voz conectado(AA LEN 30 N°REGISTROS REGISTROS ESTADOS 0A)
  if(inputString=="01234"){indiceC=10;}//reinicio
return indiceC;}

char analisis(void){
  char indiceA=0xFF;
  if (stringComplete) {//computadora
    Serial.println (inputString);
    Serial1.print  (inputString);//no puede haber salto de linea
    Serial2.println(inputString);
    Serial3.println(inputString);
    //verificar
    indiceA=comparar_mensaje();
    // clear the string:
    inputString = "";
  }
  if (stringComplete1) {//modulo de voz//solo transmitor
    Serial.println (inputString); 
    Serial2.println(inputString);
    Serial3.println(inputString);
    //verificar
    indiceA=comparar_mensaje();
    // clear the string:
    inputString = "";
  }
  if (stringComplete2) {//externo
    Serial.println (inputString);
    Serial2.println(inputString);
    Serial3.println(inputString);
    //verificar
    indiceA=comparar_mensaje();
    // clear the string:
    inputString = "";
  }
  if (stringComplete3) {//bluetooth
    Serial.println (inputString);
    Serial2.println(inputString);
    Serial3.println(inputString);
    //verificar
    indiceA=comparar_mensaje();
    // clear the string:
    inputString = "";
  }
  stringComplete  = false;
  stringComplete1 = false;
  stringComplete2 = false;
  stringComplete3 = false;
return indiceA;}

///////////////////
void comunicacion(char ind){
  char indiceF=0; indiceF=ind;
  static char indiceF_temp=0;
  if(indiceF!=indiceF_temp){
    indiceF_temp=indiceF;
    switch(ind){
      case 0:
        Serial.println ("mov: parar");
        Serial2.println("mov: parar");
        Serial3.println("mov: parar"); break;
        
      case 1:
        Serial.println ("mov: avanzar");
        Serial2.println("mov: avanzar");
        Serial3.println("mov: avanzar"); break;
      case 2:
        Serial.println ("mov: izquierda");
        Serial2.println("mov: izquierda");
        Serial3.println("mov: izquierda"); break;
      case 3:
        Serial.println ("mov: derecha");
        Serial2.println("mov: derecha");
        Serial3.println("mov: derecha");  break;
      case 4:
        Serial.println ("mov: retroceder");
        Serial2.println("mov: retroceder");
        Serial3.println("mov: retroceder");break;
      case 9:
        Serial.println ("CONECTADO");
        Serial2.println("CONECTADO");
        Serial3.println("CONECTADO");break;//call reset
      case 10:
        Serial.println ("REINICIO");
        Serial2.println("REINICIO");
        Serial3.println("REINICIO");
        delay(500);REQUEST_EXTERNAL_RESET; break;//call reset
      default:
        break;
    }
  }
return;}
