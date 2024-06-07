/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 * YWROBOT
 *Compatible with the Arduino IDE 1.0
 *Library version:1.1
 */
 
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
extern void serialEventRun(void) __attribute__((weak));

//funciones
void parpadeo();
void parar();
void izquierda();
void derecha();
void retroceder();
void avanzar();
void movimiento(char ind);

void enviar_lcd(unsigned long d);
unsigned long distancia (const char trig, const char echo);
void sensar();
void recepcion();
void serialEventRun(void) {
  if (Serial.available()) serialEvent();
  if (Serial1.available()) serialEvent1();
  digitalWrite(13, HIGH);
//  if (Serial2.available()) serialEvent2();
//  if (Serial3.available()) serialEvent3();
}



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
 *  I2C0:  20 y 21 para el lcd
 *  UART0: 00 y 01 para la pc
 *  UART1: 19 y 18 para el modulo de voz
 *  UART2: 17 y 16 para el modulo bluetooh
 */
//variables
char PWMA=0;//PWM DEL MOTOR A (0-255)
char PWMB=0;//PWM DEL MOTOR B (0-255)
char PWMF=255;//FIN PWM
char PWMI=250;//INICIO PWM
char DIR_I2C=0x27;//direccion del adress del I2C
char mov=0;
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(DIR_I2C,20,4);  

void setup(){
  //inicializar puerto serial usart
  Serial.begin(9600);//pc
  Serial1.begin(9600);//modulo de voz
//  Serial2.begin(9600);//bluetooth
//  Serial3.begin(9600);//bluetooth
  Serial.print("Bienvenido");
  inputString.reserve(30);
  Serial1.write((byte)0xAA);
  Serial1.write((byte)0x06);
  Serial1.write((byte)0x30);
  Serial1.write((byte)0x00);//puede ser interpretado como un puntero//NULL
  Serial1.write((byte)0x01);
  Serial1.write((byte)0x02);
  Serial1.write((byte)0x03);
  Serial1.write((byte)0x0A);
  delay(100);
  recepcion();
  //inicializar el lcd 
  lcd.init();                      
  lcd.backlight();
  lcd.clear();
  lcd.print(" Silla de Ruedas ");
  lcd.setCursor(0,1);
  lcd.print("       UTP      ");
  //inicializar pines
  //inicializar pines del sistema
  pinMode(led_on , OUTPUT); //pin como salida
  pinMode(led_ade, OUTPUT); //pin como salida
  pinMode(led_ret, OUTPUT); //pin como salida
  pinMode(led_izq, OUTPUT); //pin como salida
  pinMode(led_der, OUTPUT); //pin como salida
  digitalWrite(led_on , LOW);//Inicializamos el pin con 0  
  digitalWrite(led_ade, LOW);//Inicializamos el pin con 0
  digitalWrite(led_ret, LOW);//Inicializamos el pin con 0
  digitalWrite(led_izq, LOW);//Inicializamos el pin con 0
  digitalWrite(led_der, LOW);//Inicializamos el pin con 0
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

  parar();
  parpadeo();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("modulo");
  mov=1;
}
static bool a=HIGH;
void loop(){
  parpadeo();
  recepcion();
  delay(200);
  sensar();
  movimiento(mov);
  
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
bool verf=false;
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    if(inChar>0x29 & inChar<0x3A){verf=true;}
    if(verf==true){inputString += inChar;}
    if (inChar == '\n') {
      stringComplete = true;
      verf=false;
      
    }
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    
  }
return;}
void serialEvent1() {
  
  while (Serial1.available()) {
    
    // get the new byte:
    char inChar = (char)Serial1.read();
    if(inChar>0x29 & inChar<0x3A){verf=true;}
    if(verf==true){inputString += inChar;}
    if (inChar == '\n') {
      stringComplete = true;
      verf=false; 
    }
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
  }
  
return;}
//void serialEvent2() {
//  while (Serial2.available()) {
//    // get the new byte:
//    char inChar = (char)Serial2.read();
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag so the main loop can
//    // do something about it:
//    if (inChar == '\n') {
//      stringComplete = true;
//    }
//  }
//}
//void serialEvent3() {
//  while (Serial3.available()) {
//    // get the new byte:
//    char inChar = (char)Serial3.read();
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag so the main loop can
//    // do something about it:
//    if (inChar == '\n') {
//      stringComplete = true;
//    }
//  }
//}

unsigned long cuentaS=0;
void sensar(void){
  unsigned long d=0;
  unsigned long temp_d=99;
  unsigned long count=0;
    d=distancia(trig1,echo1);//no funciona
    if(d<20){if(temp_d>d){temp_d=d;}}
    if(d<10){count=count+1;}
    while(d!=0){d=0;}
    d=distancia(trig2,echo2);
    if(d<20){if(temp_d>d){temp_d=d;}}
    if(d<10){count=count+2;}
    while(d!=0){d=0;}
    d=distancia(trig3,echo3);
    if(d<20){if(temp_d>d){temp_d=d;}}
    if(d<10){count=count+2;}
    while(d!=0){d=0;}
    
    if(temp_d!=99){enviar_lcd(temp_d);}
    else{cuentaS=cuentaS+1;}
    if(cuentaS==8){lcd.clear();lcd.setCursor(0,0);lcd.print("modulo");cuentaS=0;}
    temp_d=99;
    if(count!=0){mov=0;}//me dice de donde viene el obstaculo
    count=0;
return;}
unsigned long distancia (const char trig, const char echo){
  unsigned long t=0;
  unsigned long d=0;
  digitalWrite(trig, HIGH);
  digitalWrite(trig, HIGH);
  delayMicroseconds(12);          //Enviamos un pulso de 10us
  digitalWrite(trig, LOW);
  digitalWrite(trig, LOW);
  
  t = pulseInLong(echo, HIGH);
  delayMicroseconds(200); //8 pulsos que se necesitan para que se pueda volver a activar el trigger
  d=(t)*(346.13)/20000;
  t=0;
  return d;
}

void enviar_lcd(unsigned long d){ //envio de distancia a l lcd
  unsigned long temp_d=0;
  temp_d=d;
  lcd.setCursor(0,1);// quitar para mandar una posicion
  
  char buf [6]="00";//char buf [6]="";
  ultoa(temp_d,buf,10);
  for(char i=0;i<6;i++){
    if((buf[i]>=0x30) & (buf[i]<=0x39)){lcd.write(buf[i]);
  }}
  lcd.print("cm.  ");
  while(temp_d!=0){temp_d=0;}
  delay(100);
return;}

void movimiento(char ind){
  switch(ind){
    case 0:
      parar();
      digitalWrite(led_on , LOW );
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, LOW );
      break;
      
    case 1:
      avanzar();
      digitalWrite(led_on , HIGH);
      digitalWrite(led_ade, HIGH);
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, LOW );
      break;
      
    case 2:
      izquierda();
      digitalWrite(led_on , HIGH);
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, HIGH);
      digitalWrite(led_der, LOW );
      break;
      
    case 3:
      derecha();
      digitalWrite(led_on , HIGH);
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, HIGH);
      break;
      
    case 4:
      retroceder();
      digitalWrite(led_on , HIGH);
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, HIGH);
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, LOW );
      break;
      
    default:
      parar();
      digitalWrite(led_on , LOW );
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, LOW );
      break;
   }
return;}
void avanzar(void){
  PWMA=PWMI;
  PWMB=PWMI;
  analogWrite(motAPWM, PWMA);
  analogWrite(motBPWM, PWMB);
  digitalWrite(motA_P1, LOW );
  digitalWrite(motA_P2, HIGH);
  digitalWrite(motB_P1, LOW );
  digitalWrite(motB_P2, HIGH);
return;}
void retroceder(void){
  PWMA=PWMI;
  PWMB=PWMI;
  analogWrite(motAPWM, PWMA);
  analogWrite(motBPWM, PWMB);   
  digitalWrite(motA_P1, HIGH);
  digitalWrite(motA_P2, LOW );
  digitalWrite(motB_P1, HIGH);
  digitalWrite(motB_P2, LOW );
return;}
void izquierda(void){
  PWMA=PWMI;
  PWMB=PWMI;
  analogWrite(motAPWM, PWMA);
  analogWrite(motBPWM, PWMB);   
  digitalWrite(motA_P1, LOW );
  digitalWrite(motA_P2, LOW );
  digitalWrite(motB_P1, LOW );//ACTIVAR MOTOR DERECHO PARA IR A LA IZQUIERDA
  digitalWrite(motB_P2, HIGH );
return;}
void derecha(void){
  PWMA=PWMI;
  PWMB=PWMI;
  analogWrite(motAPWM, PWMA);
  analogWrite(motBPWM, PWMB);     
  digitalWrite(motA_P1, LOW );//ACTIVAR MOTOR IZQUIERDA PARA IR A LA DERECHO
  digitalWrite(motA_P2, HIGH);
  digitalWrite(motB_P1, LOW );
  digitalWrite(motB_P2, LOW );
return;}
void parar(void){
  PWMA=0;
  PWMB=0;
  analogWrite(motAPWM, PWMA);
  analogWrite(motBPWM, PWMB);
  digitalWrite(motA_P1, LOW);//Inicializamos el pin con 0
  digitalWrite(motA_P2, LOW);//Inicializamos el pin con 0
  digitalWrite(motB_P1, LOW);//Inicializamos el pin con 0
  digitalWrite(motB_P2, LOW);//Inicializamos el pin con 0
return;}

void parpadeo (void){
  for(char i=0;i<10;i++){
    digitalWrite(led_on, HIGH);
    delay(50);
    digitalWrite(led_on, LOW );
    delay(50);
  }
return;}
