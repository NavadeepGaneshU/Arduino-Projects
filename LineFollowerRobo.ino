//Line follower  robo @github@Navadeep Ganesh U


LIR-LEST IR SENSOR

CIR-CENTRAL IR SENSOR

RIR-RIGHT IR SENSOR

ML-LEFT MOTOR

MR-RIGHT MOTOR

const int LIR=13;

const int CIR=12;

const int RIR=8;

const int ML=A0;

const int MR=A1;

int val1=0,val2=0,val3=0;

void setup()

{

pinMode(LIR,INPUT);

pinMode(CIR,INPUT);

pinMode(RIR,INPUT);

pinMode(ML,OUTPUT);

pinMode(MR,OUTPUT);

}

void loop()

{

val1=digitalRead(LIR);

val2=digitalRead(CIR);

val3=digitalRead(RIR);

if(val1==HIGH && val2==LOW && val3==HIGH)

{

digitalWrite(ML,HIGH);

digitalWrite(MR,HIGH);

}

if(val1==LOW && val2==HIGH && val3==HIGH)

{

digitalWrite(ML,LOW);

digitalWrite(MR,HIGH);

}

if(val1==HIGH && val2==HIGH && val3==LOW)

{

digitalWrite(ML,HIGH);

digitalWrite(MR,LOW);

}

}