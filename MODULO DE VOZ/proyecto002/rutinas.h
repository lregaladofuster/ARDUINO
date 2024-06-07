
#include "configproy.h"




void parpadeo (void){
  for(char i=0;i<10;i++){
    digitalWrite(led_on, HIGH);
    delay(50);
    digitalWrite(led_on, LOW );
    delay(50);
  }
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

void movimiento(char ind){
  switch(ind){
    case 0:
      //parar();
      digitalWrite(led_on , LOW );
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, LOW );
      break;
      
    case 1:
      //avanzar();
      digitalWrite(led_on , HIGH);
      digitalWrite(led_ade, HIGH);
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, LOW );
      break;
      
    case 2:
      //izquierda();
      digitalWrite(led_on , HIGH);
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, HIGH);
      digitalWrite(led_der, LOW );
      break;
      
    case 3:
      //derecha();
      digitalWrite(led_on , HIGH);
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, HIGH);
      break;
      
    case 4:
      //retroceder();
      digitalWrite(led_on , HIGH);
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, HIGH);
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, LOW );
      break;
      
    default:
      //parar();
      digitalWrite(led_on , LOW );
      digitalWrite(led_ade, LOW );
      digitalWrite(led_ret, LOW );
      digitalWrite(led_izq, LOW );
      digitalWrite(led_der, LOW );
      break;
   }
return;}
