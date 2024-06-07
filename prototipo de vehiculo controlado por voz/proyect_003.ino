
#include "configproy.h"
#include "encoder.h"
#include "leds.h"
#include "motor.h"
#include "ultrasonido.h"
#include "serial.h"
#include "mensajes_lcd.h"
#include "rutinas.h"

unsigned char indice_principal=0;
unsigned char indice_temp=0;


void setup() {
  config_usart();
  config_voz();
  config_lcdi2c();
  config_ultrasonido();
  config_motor();
  config_encoder();
}

unsigned long d1=0;
void loop() {
  indice_principal=(indice_principal)&(sensar());
  movimiento(indice_principal);
  comunicacion(indice_principal);
  readSerial();
  indice_temp=indice_principal;
  indice_principal=analisis();
  if(indice_principal==0xFF){indice_principal=indice_temp;}
}
