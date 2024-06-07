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
#include "configproy.h"
#include "serialv.h"
#include "motorv.h"
#include "rutinas.h"

//variables

char DIR_I2C=0x27;//direccion del adress del I2C
char mov=0;

// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(DIR_I2C,20,4);  

void setup(){
  //inicializar el lcd 
  lcd.init();                      
  lcd.backlight();
  lcd.clear();
  lcd.print(" Silla de Ruedas ");
  lcd.setCursor(0,1);
  lcd.print("       UTP      ");
  
  config_usart();
  //inicializar pines

  Serial.print("Bienvenido");

}

void loop(){
  
}
