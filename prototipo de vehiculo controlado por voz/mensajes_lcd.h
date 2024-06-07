
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//variables
char DIR_I2C=0x27;//direccion del adress del I2C
LiquidCrystal_I2C lcd(DIR_I2C,20,4);

void config_lcdi2c(void){
  lcd.init();                      
  lcd.backlight();
  lcd.clear();
  lcd.print(" Silla de Ruedas ");
  lcd.setCursor(0,1);
  lcd.print("       UTP      ");
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);delayMicroseconds(15000);
  lcd.clear();lcd.setCursor(0,0);lcd.print("     modulo     ");
return;}

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
  delayMicroseconds(5000);
return;}
