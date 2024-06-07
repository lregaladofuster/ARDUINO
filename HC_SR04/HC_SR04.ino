
#include <stdio.h>
#include <math.h>

const char Trigger = 23;   //Pin digital 2 para el Trigger del sensor
const char Echo = 22;   //Pin digital 3 para el Echo del sensor
const char led= 13;

void setup() {
  Serial.begin(9600);//iniciailzamos la comunicación
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop(){
  unsigned long duracion=0;
  unsigned long distancia=0;
   
  digitalWrite(Trigger, HIGH);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(12);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  digitalWrite(Trigger, LOW);
  
  duracion = pulseInLong(Echo, HIGH);
  delayMicroseconds(200); //8 pulsos que se necesitan para que se pueda volver a activar el trigger
  distancia=(duracion)*(346.13)/20000;
  /*while(digitalRead(Echo)==LOW);
  while(digitalRead(Echo)==HIGH){
    c1=c1+1;
    delayMicroseconds(5); //HC-SR04 trabaja a 40Khz=25us
  }*/
  if(distancia>10){digitalWrite(led, HIGH);}
  else{digitalWrite(led, LOW);}
  
  Serial.print("distancia:");
  Serial.print(distancia);  
  Serial.print("cm");
  Serial.print("     y     ");
  Serial.print("tiempo:");
  Serial.print(duracion);  
  Serial.print("us");
  Serial.println();
  duracion=0;
  distancia=0;
  if(duracion!=0){duracion=0;}
  if(distancia!=0){distancia=0;}
  
          
}
