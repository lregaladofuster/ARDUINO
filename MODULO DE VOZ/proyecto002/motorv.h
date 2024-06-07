
#include "configproy.h"

char PWMA=0;//PWM DEL MOTOR A (0-255)
char PWMB=0;//PWM DEL MOTOR B (0-255)
char PWMF=255;//FIN PWM
char PWMI=250;//INICIO PWM

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
}

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
