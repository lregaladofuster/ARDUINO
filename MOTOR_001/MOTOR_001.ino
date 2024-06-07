//pines de los motores
const char motAPWM = 9;//PIN DEL PWM DEL MOTOR B //ENABLE B DEL MODULO DE POTENCIA//IZQUIERDO
const char motBPWM = 8;//PIN DEL PWM DEL MOTOR A //ENABLE A DEL MODULO DE POTENCIA//DERECHO
const char motA_P1 = 42;//IN4 DEL MODULO DE POTENCIA PARA EL MOTOR A
const char motA_P2 = 43;//IN3 DEL MODULO DE POTENCIA PARA EL MOTOR A
const char motB_P1 = 41;//IN2 DEL MODULO DE POTENCIA PARA EL MOTOR B
const char motB_P2 = 40;//IN1 DEL MODULO DE POTENCIA PARA EL MOTOR B
const char motAENC = 51;//PIN DEL ENCODER DEL MOTOR A
const char motBENC = 53;//PIN DEL ENCODER DEL MOTOR B
unsigned char PWM0=255;

void motor(char PWM12){
  analogWrite(motAPWM, PWM12);
  analogWrite(motBPWM, PWM12);
}

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
  
  digitalWrite(motA_P1, LOW );
  digitalWrite(motA_P2, HIGH);
  digitalWrite(motB_P1, LOW );
  digitalWrite(motB_P2, HIGH);
  delay(1000);
  motor(PWM0);
  delay(10);
}

void loop() {
  motor(255);
  delay(1);
  motor(80);
  delay(100);
}

void serialEvent() {
  if (Serial.available()) {
    PWM0 = (unsigned char)Serial.read();
  }
}
