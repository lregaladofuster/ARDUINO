//pines de los motores
const char motAPWM = 9;//PIN DEL PWM DEL MOTOR B //ENABLE B DEL MODULO DE POTENCIA//IZQUIERDO
const char motBPWM = 8;//PIN DEL PWM DEL MOTOR A //ENABLE A DEL MODULO DE POTENCIA//DERECHO
const char motA_P1 = 42;//IN4 DEL MODULO DE POTENCIA PARA EL MOTOR A
const char motA_P2 = 43;//IN3 DEL MODULO DE POTENCIA PARA EL MOTOR A
const char motB_P1 = 41;//IN2 DEL MODULO DE POTENCIA PARA EL MOTOR B
const char motB_P2 = 40;//IN1 DEL MODULO DE POTENCIA PARA EL MOTOR B
const char motAENC = 51;//PIN DEL ENCODER DEL MOTOR A
const char motBENC = 53;//PIN DEL ENCODER DEL MOTOR B



volatile unsigned char PWM_temp=0;
//limites
unsigned char PWMF=130;//FIN PWM
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
void setup() {
  Serial.begin(9600);
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

void loop() {
  avanzar();
  //unsigned long previousMillis = millis();        // will store last time LED was updated
  //const long interval = 100;  
  while(1){
    //unsigned long currentMillis = millis();
    //
    //if (currentMillis - previousMillis >= interval) {
    //  previousMillis = currentMillis;
    //  Serial.println(currentMillis);
    //}
    while(!digitalRead(motAENC));
    unsigned long t1=pulseInLong(motAENC,LOW);
    while(digitalRead(motAENC));
    unsigned long t2=pulseInLong(motAENC,HIGH);
    t1=t1+t2;
    t1=t1*20;//tiempo(micro) en que hace una revolucion
    unsigned long RPM=60*1000*1000/t1;
    Serial.print("RPM ");
    Serial.println(RPM);
  }
}
