

void parpadeo (void){
  for(char i=0;i<30;i++){
    digitalWrite(led_on, HIGH);
    delayMicroseconds(15000);
    digitalWrite(led_on, LOW );
    delayMicroseconds(15000);
  }
return;}
