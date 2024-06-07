


unsigned char PWM_temp=0;//limites
unsigned char PWMF=200;//FIN PWM
unsigned char PWMI=130;//INICIO PWM
unsigned char PWMP=00;//nulo

void velocidad(unsigned char vel){
  PWM_temp=vel;
  analogWrite(motAPWM,vel);
  analogWrite(motBPWM,vel);
return;}
void avanzar(void){
  velocidad(PWMF);
  digitalWrite(motA_P1, LOW );
  digitalWrite(motA_P2, HIGH);
  digitalWrite(motB_P1, LOW );
  digitalWrite(motB_P2, HIGH);
return;}
void retroceder(void){
  velocidad(PWMF);
  digitalWrite(motA_P1, HIGH);
  digitalWrite(motA_P2, LOW );
  digitalWrite(motB_P1, HIGH);
  digitalWrite(motB_P2, LOW );
return;}
void izquierda(void){
  velocidad(PWMF);  
  digitalWrite(motA_P1, LOW );
  digitalWrite(motA_P2, LOW );
  digitalWrite(motB_P1, LOW );//ACTIVAR MOTOR DERECHO PARA IR A LA IZQUIERDA
  digitalWrite(motB_P2, HIGH );
return;}
void derecha(void){
  velocidad(PWMF);
  digitalWrite(motA_P1, LOW );//ACTIVAR MOTOR IZQUIERDA PARA IR A LA DERECHO
  digitalWrite(motA_P2, HIGH);
  digitalWrite(motB_P1, LOW );
  digitalWrite(motB_P2, LOW );
return;}
void parar(void){
  velocidad(PWMP);
  digitalWrite(motA_P1, LOW);//Inicializamos el pin con 0
  digitalWrite(motA_P2, LOW);//Inicializamos el pin con 0
  digitalWrite(motB_P1, LOW);//Inicializamos el pin con 0
  digitalWrite(motB_P2, LOW);//Inicializamos el pin con 0
return;}
