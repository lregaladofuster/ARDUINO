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

//funciones
void parpadeo();
void enviar_lcd(unsigned long d);
unsigned long distancia (const char trig, const char echo);
void sensar(void);

//pines
//el sentido de asignacion de pines es de izquierda a derecha
//pines de sensores
const char echo1 = 53;
const char trig1 = 52;
const char echo2 = 51;
const char trig2 = 50;
const char led_on= 13;
/* otros pines:
 *  I2C0:  20 y 21 para el lcd
 *  UART0: 00 y 01 para la pc
 *  UART1: 19 y 18 para el modulo de voz
 *  UART2: 17 y 16 para el modulo bluetooh
 */
//variables
char DIR_I2C=0x27;//direccion del adress del I2C

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(DIR_I2C,20,4);  

void setup()
{
  //inicializar el lcd 
  lcd.init();                      
  lcd.backlight();
  lcd.clear();
  lcd.print(" Silla de Ruedas ");
  lcd.setCursor(0,1);
  lcd.print("       UTP      ");
  
  //inicializar puerto serial usart
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  
  //inicializar pines
  //inicializar pines del sistema
  pinMode(led_on , OUTPUT); //pin como salida
  digitalWrite(led_on , LOW);//Inicializamos el pin con 0  
  //inicializar pines del sensor
  pinMode(trig1, OUTPUT); //pin como salida
  pinMode(echo1, INPUT );  //pin como entrada
  pinMode(trig2, OUTPUT); //pin como salida
  pinMode(echo2, INPUT );  //pin como entrada
  digitalWrite(trig1, LOW);//Inicializamos el pin con 0
  digitalWrite(trig2, LOW);//Inicializamos el pin con 0
  
  parpadeo();
  delay(2000);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("modulo");
  sensar();
  delay(500);
  
}





void sensar(void){
  unsigned long d=0;
  unsigned long temp_d=99;
  unsigned long count=0;
  d=distancia(trig1,echo1);
  if(d<20){temp_d=d;}
  if(d>10){count=count+1;}
  while(d!=0){d=0;}
  d=distancia(trig2,echo2);
  if(d<20){if(temp_d>d){temp_d=d;}}
  if(d>10){count=count+2;}
  while(d!=0){d=0;}
  
  if(temp_d!=99){enviar_lcd(temp_d);}
  
  temp_d=99;
  while(count!=0){
    //parada
    count=0;
  }
}

unsigned long distancia (char trig, char echo){
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
  
  char buf [6]="";
  ultoa(temp_d,buf,10);
  for(char i=0;i<6;i++){
    if((buf[i]>=0x30) & (buf[i]<=0x39)){lcd.write(buf[i]);
  }}
  lcd.print("cm.");
  while(temp_d!=0){temp_d=0;}
  delay(10);
}











void parpadeo (void){
  for(char i=0;i<10;i++){
    digitalWrite(led_on, HIGH);
    delay(15);
    digitalWrite(led_on, LOW );
    delay(15);
  }
}
