//necesito revisar timer0

unsigned long RPM_A(void){
    while(!digitalRead(motAENC));
    unsigned long t11=pulseInLong(motAENC,LOW);
    while(digitalRead(motAENC));
    unsigned long t12=pulseInLong(motAENC,HIGH);
    t11=t11+t12;
    t11=t11*20;//tiempo(micro) en que hace una revolucion
    unsigned long RPM=60*1000*1000/t11;
    return RPM;
}

unsigned long RPM_B(void){
    while(!digitalRead(motBENC));
    unsigned long t11=pulseInLong(motBENC,LOW);
    while(digitalRead(motBENC));
    unsigned long t12=pulseInLong(motBENC,HIGH);
    t11=t11+t12;
    t11=t11*20;//tiempo(micro) en que hace una revolucion
    unsigned long RPM=60*1000*1000/t11;
    return RPM;
}
