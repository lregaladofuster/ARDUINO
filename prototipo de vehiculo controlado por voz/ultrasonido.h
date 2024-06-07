

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
