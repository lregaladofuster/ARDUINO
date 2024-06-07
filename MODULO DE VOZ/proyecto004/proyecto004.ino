

#include <string>
#include <cstring>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,4);

#define SYSRESETREQ    (1<<2)
#define VECTKEY        (0x05fa0000UL)
#define VECTKEY_MASK   (0x0000ffffUL)
#define AIRCR          (*(uint32_t*)0xe000ed0cUL) // fixed arch-defined address
#define REQUEST_EXTERNAL_RESET (AIRCR=(AIRCR&VECTKEY_MASK)|VECTKEY|SYSRESETREQ)

//pines
//el sentido de asignacion de pines es de izquierda a derecha
//pines de sensores
const char echo1 = 25;//izquierda
const char trig1 = 24;
const char echo2 = 23;//derecha
const char trig2 = 22;
const char echo3 = 27;//atraa
const char trig3 = 26;
//pines de los motores
const char motAPWM = 9;//PIN DEL PWM DEL MOTOR B //ENABLE B DEL MODULO DE POTENCIA//IZQUIERDO
const char motBPWM = 8;//PIN DEL PWM DEL MOTOR A //ENABLE A DEL MODULO DE POTENCIA//DERECHO
const char motA_P1 = 42;//IN4 DEL MODULO DE POTENCIA PARA EL MOTOR A
const char motA_P2 = 43;//IN3 DEL MODULO DE POTENCIA PARA EL MOTOR A
const char motB_P1 = 41;//IN2 DEL MODULO DE POTENCIA PARA EL MOTOR B
const char motB_P2 = 40;//IN1 DEL MODULO DE POTENCIA PARA EL MOTOR B
const char motAENC = 51;//PIN DEL ENCODER DEL MOTOR A
const char motBENC = 53;//PIN DEL ENCODER DEL MOTOR B
//pines de los leds
const char led_on  = 13;//led del sistema/led de marcha y parada del carro
const char led_ade = 14;
const char led_ret = 16;
const char led_der = 17;
const char led_izq = 18;
/* otros pines:
    I2C0:  20 y 21 para el lcd
    UART0: 00 y 01 para la pc
    UART1: 19 y 18 para el modulo de voz
    UART2: 17 y 16 para el modulo bluetooh
*/
void config_ultrasonido() {
  //inicializar pines del sensor
  pinMode(trig1, OUTPUT); //pin como salida
  pinMode(echo1, INPUT );  //pin como entrada
  pinMode(trig2, OUTPUT); //pin como salida
  pinMode(echo2, INPUT );  //pin como entrada
  pinMode(trig3, OUTPUT); //pin como salida
  pinMode(echo3, INPUT );  //pin como entrada
  digitalWrite(trig1, LOW);//Inicializamos el pin con 0
  digitalWrite(trig2, LOW);//Inicializamos el pin con 0
  digitalWrite(trig3, LOW);//Inicializamos el pin con 0
return;}

void config_motor(){
  //inicializar pines del motor
  pinMode(motAPWM, OUTPUT); //pin como salida
  pinMode(motA_P1, OUTPUT); //pin como salida
  pinMode(motA_P2, OUTPUT); //pin como salida
  pinMode(motAENC, INPUT ); //pin como entrada
  pinMode(motBPWM, OUTPUT); //pin como salida
  pinMode(motB_P1, OUTPUT); //pin como salida
  pinMode(motB_P2, OUTPUT); //pin como salida
  pinMode(motBENC, INPUT ); //pin como entrada
  digitalWrite(motAPWM, LOW);//Inicializamos el pin con 0  
  digitalWrite(motA_P1, LOW);//Inicializamos el pin con 0
  digitalWrite(motA_P2, LOW);//Inicializamos el pin con 0
  digitalWrite(motBPWM, LOW);//Inicializamos el pin con 0  
  digitalWrite(motB_P1, LOW);//Inicializamos el pin con 0
  digitalWrite(motB_P2, LOW);//Inicializamos el pin con 0
return;}
void config_encoder(){
  //inicializar pines del encoder
  pinMode(motAENC, INPUT ); //pin como entrada
  pinMode(motBENC, INPUT ); //pin como entrada
return;}

String inputString = "";         // a String to hold incoming data
byte mensaje01[]="bienvenido";
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
  Serial.write(mensaje01, sizeof(mensaje01));
  Serial3.write(mensaje01, sizeof(mensaje01));
  //Serial.println("bienvenido");
return;}

void config_voz(){
    Serial1.write((byte)0xAA);
    Serial1.write((byte)0x07);
    Serial1.write((byte)0x30);
    Serial1.write((byte)0x00);//puede ser interpretado como un puntero//NULL
    Serial1.write((byte)0x01);
    Serial1.write((byte)0x02);
    Serial1.write((byte)0x03);
    Serial1.write((byte)0x04);
    Serial1.write((byte)0x0A);
    delayMicroseconds(100);
    inputString = "";         // a String to hold incoming data
    stringComplete = false;  // whether the string is complete
    stringComplete1 = false;  // whether the string is complete
    stringComplete2 = false;
    stringComplete3 = false;
return;}

void readSerial(void) {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if(inChar>0x29 & inChar<0x3A){inputString += inChar;}
    if(inChar == '\n') {stringComplete = true;}
  }
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    if(inChar>0x29 & inChar<0x3A){inputString += inChar;}
    if(inChar == '\n') {stringComplete1= true;}
  }
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    if(inChar>0x29 & inChar<0x3A){inputString += inChar;}
    if(inChar == '\n') {stringComplete2= true;}
  }
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    if(inChar>0x29 & inChar<0x3A){inputString += inChar;}
    if(inChar == '\n') {stringComplete3= true;}
  }
return;}

char comparar_mensaje(){
    static char indiceC=0;
    static char indiceC_temp=0;
    if(inputString=="00"){indiceC=0;}
    if(inputString=="01"){indiceC=1;}
    if(inputString=="02"){indiceC=2;}
    if(inputString=="03"){indiceC=3;}
    if(inputString=="04"){indiceC=4;}
    if(inputString=="01234"){indiceC=10;}
    if(indiceC!=indiceC_temp){
      lcd.setCursor(8,0);
      lcd.print("mov:");
      lcd.print(inputString[0]);
      lcd.print(inputString[1]);
      indiceC_temp=indiceC;
    }
return indiceC;}

char analisis(void){
  char indiceA=0xFF;
  if (stringComplete) {//computadora
    Serial.println (inputString); delayMicroseconds(1);
    Serial1.print  (inputString); delayMicroseconds(1);//no puede haber salto de linea
    Serial2.println(inputString); delayMicroseconds(1);
    Serial3.println(inputString); delayMicroseconds(1);
    //verificar
    indiceA=comparar_mensaje();
    // clear the string:
    inputString = "";
  }
  if (stringComplete1) {//modulo de voz//solo transmitor
    Serial.println (inputString); delayMicroseconds(1);
    Serial2.println(inputString); delayMicroseconds(1);
    Serial3.println(inputString); delayMicroseconds(1);
    //verificar
    indiceA=comparar_mensaje();
    // clear the string:
    inputString = "";
  }
  if (stringComplete2) {//externo
    Serial.println (inputString); delayMicroseconds(1);
    Serial1.print  (inputString); delayMicroseconds(1);//no puede haber salto de linea
    Serial2.print  (inputString); delayMicroseconds(1);
    Serial3.println(inputString); delayMicroseconds(1);
    //verificar
    indiceA=comparar_mensaje();
    // clear the string:
    inputString = "";
  }
  if (stringComplete3) {//bluetooth
    Serial.println (inputString); delayMicroseconds(1);
    Serial1.print  (inputString); delayMicroseconds(1);//no puede haber salto de linea
    Serial2.println(inputString); delayMicroseconds(1);
    Serial3.println(inputString); delayMicroseconds(1);
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

void comunicacion(char ind){
  char indiceF=0; indiceF=ind;
  static char indiceF_temp=0;
  if(indiceF!=indiceF_temp){
    indiceF_temp=indiceF;
    switch(ind){
      case 0:
        Serial.println ("mov: parar");
        Serial2.println("mov: parar");
        Serial3.println("mov: parar"); 
        digitalWrite(motAPWM, LOW);
        digitalWrite(motBPWM, LOW);
        digitalWrite(motA_P1, LOW);//Inicializamos el pin con 0
        digitalWrite(motA_P2, LOW);//Inicializamos el pin con 0
        digitalWrite(motB_P1, LOW);//Inicializamos el pin con 0
        digitalWrite(motB_P2, LOW);//Inicializamos el pin con 0
        break;
        
      case 1:
        Serial.println ("mov: avanzar");
        Serial2.println("mov: avanzar");
        Serial3.println("mov: avanzar"); 
        digitalWrite(motAPWM, HIGH);
        digitalWrite(motBPWM, HIGH);
        digitalWrite(motA_P1, LOW );
        digitalWrite(motA_P2, HIGH);
        digitalWrite(motB_P1, LOW );
        digitalWrite(motB_P2, HIGH);
        break;
        
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
      case 10:
        Serial.println ("reinicio");
        Serial2.println("reinicio");
        Serial3.println("reinicio");
        delay(500);
        REQUEST_EXTERNAL_RESET;  //call reset
        break;
      default:
        break;
    }
  }
return;}


unsigned char indice_principal=0;
unsigned char indice_temp=0;

void setup() {
  interrupts();
  config_usart();
  config_voz();
  Serial.flush();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Silla de Ruedas");
  lcd.setCursor(0,1);
  lcd.print("      UTP      ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("modulo         ");
  config_ultrasonido();
  config_motor();
  config_encoder();
}


void loop() {
  comunicacion(indice_principal);
  readSerial();
  indice_temp=indice_principal;
  indice_principal=analisis();
  if(indice_principal==0xFF){indice_principal=indice_temp;}

  
}
