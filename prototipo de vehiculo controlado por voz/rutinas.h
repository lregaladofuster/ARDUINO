
unsigned long cuentaS=0;

char sensar(void){//NECESITA TRABAJAR CON DOS VARIABLES:MOVIMIENTO(ADONDE NOS QUEREMOS MOVER) Y VARIABLE COUNT(DE DONDE PROVIENE EL BLOQUEO)
  unsigned char indiceS=0xFF;
  unsigned long d=0;
  unsigned long temp_d=99;
  unsigned char count=0;
  d=distancia(trig1,echo1);//no funciona
  if(d<20){ if(temp_d>d){temp_d=d;}
            if(d<18){count|=0b00000001;}else{count&=0b11111110;}}
            while(d!=0){d=0;}
  d=distancia(trig2,echo2);
  if(d<20){ if(temp_d>d){temp_d=d;}
            if(d<18){count|=0b00000010;}else{count&=0b11111101;}}
            while(d!=0){d=0;}
  d=distancia(trig3,echo3);
  if(d<20){ if(temp_d>d){temp_d=d;}
            if(d<18){count|=0b00000100;}else{count&=0b11111011;}}
            while(d!=0){d=0;}
  
  if(temp_d!=99){enviar_lcd(temp_d);}//if(temp_d!=99 & temp_d!=0){enviar_lcd(temp_d);}
  else{cuentaS=cuentaS+1;}
  if(cuentaS==8){lcd.setCursor(0,1);lcd.print("              ");cuentaS=0;}
  temp_d=99;
  if(count!=0){indiceS=0;}//me dice de donde viene el obstaculo
  count=0;
return indiceS;}

void movimiento(char ind){
  switch(ind){
    case 0:
      parar();break;
    case 1:
      avanzar();break;
    case 2:
      izquierda();break;
    case 3:
      derecha();break;
    case 4:
      retroceder();break;
    default:
      parar();break;
   }
return;}
