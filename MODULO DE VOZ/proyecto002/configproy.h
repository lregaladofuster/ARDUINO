
//pines
//el sentido de asignacion de pines es de izquierda a derecha
//pines de sensores
const char echo1 = 25;//izquierda
const char trig1 = 24;
const char echo2 = 23;//derecha
const char trig2 = 22;
const char echo3 = 27;//atraa
const char trig3 = 26;
//pines de los motores
const char motAPWM = 9;//PIN DEL PWM DEL MOTOR B //ENABLE B DEL MODULO DE POTENCIA//IZQUIERDO
const char motBPWM = 8;//PIN DEL PWM DEL MOTOR A //ENABLE A DEL MODULO DE POTENCIA//DERECHO
const char motA_P1 = 42;//IN4 DEL MODULO DE POTENCIA PARA EL MOTOR A
const char motA_P2 = 43;//IN3 DEL MODULO DE POTENCIA PARA EL MOTOR A
const char motB_P1 = 41;//IN2 DEL MODULO DE POTENCIA PARA EL MOTOR B
const char motB_P2 = 40;//IN1 DEL MODULO DE POTENCIA PARA EL MOTOR B
const char motAENC = 51;//PIN DEL ENCODER DEL MOTOR A
const char motBENC = 53;//PIN DEL ENCODER DEL MOTOR B
//pines de los leds
const char led_on  = 13;//led del sistema/led de marcha y parada del carro
const char led_ade = 14;
const char led_ret = 16;
const char led_der = 17;
const char led_izq = 18;
/* otros pines:
    I2C0:  20 y 21 para el lcd
    UART0: 00 y 01 para la pc
    UART1: 19 y 18 para el modulo de voz
    UART2: 17 y 16 para el modulo bluetooh
*/

void config_led() {
  //inicializar pines del sistema
  pinMode(led_on , OUTPUT); //pin como salida
  pinMode(led_ade, OUTPUT); //pin como salida
  pinMode(led_ret, OUTPUT); //pin como salida
  pinMode(led_izq, OUTPUT); //pin como salida
  pinMode(led_der, OUTPUT); //pin como salida
  digitalWrite(led_on , LOW);//Inicializamos el pin con 0
  digitalWrite(led_ade, LOW);//Inicializamos el pin con 0
  digitalWrite(led_ret, LOW);//Inicializamos el pin con 0
  digitalWrite(led_izq, LOW);//Inicializamos el pin con 0
  digitalWrite(led_der, LOW);//Inicializamos el pin con 0
}

//sensor de distancia
void config_senD() {
  //inicializar pines del sensor
  pinMode(trig1, OUTPUT); //pin como salida
  pinMode(echo1, INPUT );  //pin como entrada
  pinMode(trig2, OUTPUT); //pin como salida
  pinMode(echo2, INPUT );  //pin como entrada
  pinMode(trig3, OUTPUT); //pin como salida
  pinMode(echo3, INPUT );  //pin como entrada
  digitalWrite(trig1, LOW);//Inicializamos el pin con 0
  digitalWrite(trig2, LOW);//Inicializamos el pin con 0
  digitalWrite(trig3, LOW);//Inicializamos el pin con 0
}
