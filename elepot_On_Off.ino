
//#include<PID_v1.h>

#define PWM_pin   13

double Vo, E, Ref;
double sensorValue;
double Output;
int D=170;
int D1 = 65, Dmin = 60;
int Vi=2455;


void setup()
{
  pinMode(PWM_pin, OUTPUT);
  pinMode(0, INPUT);
  Serial.begin(9600);

//MUDA  AFREQUENCIA DE CHAVEAMENTO PARA 30 KHZ
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00); 
  TCCR0B = _BV(CS00); 
}
  

void loop() {
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00); 
  TCCR0B = _BV(CS00); 
  delay(100);
  sensorValue = analogRead(A0);
  Ref = 4910;
  Vo = sensorValue * 11.0;
  
  if (Vo<=1.0)
  D1 = 60;
  else if(Vo>=1.10*Ref){
      D1++;
      Dmin = 70;
  }
  else if(Vo>Ref*1.05)
  {
      D1++;
      Dmin = 65;
  }
  else if(Vo<Ref*0.9){
    D1--;
    Dmin = 35;
  }
  else if(Vo<Ref*0.95){
      D1--;
      Dmin = 50;
  }
  
  if(D1<=Dmin)
    D1 =Dmin;
  else if(D1>=84)
    D1 = 84;

 
  Serial.print("\t D1 = ");
  Serial.println(D1);
  
  Serial.print("\t Dmin = ");
  Serial.println(Dmin);

  analogWrite(13, D1);
  
}
