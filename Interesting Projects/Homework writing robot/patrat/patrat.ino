int Index;
int p=2;
void setup() 
{
  pinMode(8, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(6, OUTPUT);
  pinMode(2, OUTPUT); //Direction
  pinMode(3, OUTPUT);
  digitalWrite(8,LOW);
}

void loop() 
{
  if(p==1)
  {
     digitalWrite(6,HIGH);
     for(Index = 0; Index < 200000; Index++)
      {
         digitalWrite(3,HIGH);
         delayMicroseconds(50);
         digitalWrite(3,LOW);
         delayMicroseconds(50);
       }
  }
  //delay(1000);
  if(p==2)
  {
    digitalWrite(5,LOW);

     for(Index = 0; Index < 2000; Index++)
      {
        digitalWrite(2,HIGH);
        delayMicroseconds(20);
        digitalWrite(2,LOW);
        delayMicroseconds(20);
      }
  }
  
}
