
#include <stdio.h>
#include <math.h>
#include <TimerOne.h>

const char Motor1_D=42;//pin digital
const char Motor1_I=43;//pin digital
const char ENA_M1=9; //enable del M1, (PWM)
const char ENC_M1=51;
const char led= 13;
volatile unsigned long blinkCount = 0; // La definimos como volatile, interrupcion

void derecha();
void izquierda();
  
void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  Timer1.initialize(1000);         // Dispara cada 1ms(puede llegar a 250'000)
  Timer1.attachInterrupt(ISR_Cuenta); // Activa la interrupcion y la asocia a ISR_Blink
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
  pinMode(Motor1_D, OUTPUT); //pin como salida
  pinMode(Motor1_I, OUTPUT);  //pin como salida
  pinMode(ENA_M1  , OUTPUT); //pin como salida
  pinMode(ENC_M1  , INPUT );  //pin como salida
  
  digitalWrite(Motor1_D, LOW);
  digitalWrite(Motor1_I, LOW);
  digitalWrite(ENA_M1  , LOW);
  analogWrite(ENA_M1, 150)//0-255; frecuencia 1000Hz
}


int cuenta=0;
void loop(){
  derecha();
  while(1){
    if(digitalRead(ENC_M1)==1){
      cuenta=cuenta+1;
      while(digitalRead(ENC_M1)==1);
    }
  } 
}  

void derecha(){
  digitalWrite(Motor1_D, HIGH);
  digitalWrite(Motor1_I, LOW );
}
  
void izquierda(){
  digitalWrite(Motor1_D, LOW );
  digitalWrite(Motor1_I, HIGH);
}

void ISR_Cuenta(){   
  Serial.print("cuenta:");
  Serial.print(cuenta);  
  Serial.println();
  cuenta=0;
}
