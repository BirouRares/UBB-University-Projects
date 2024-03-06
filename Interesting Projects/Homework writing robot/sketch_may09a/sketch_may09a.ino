int Index;

void setup() 
{
  pinMode(8, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(2, OUTPUT); //Direction

  digitalWrite(8,LOW);
}

void loop() 
{
  digitalWrite(5,HIGH);

  for(Index = 0; Index < 2000; Index++)
  {
    digitalWrite(2,HIGH);
    delayMicroseconds(500);
    digitalWrite(2,LOW);
    delayMicroseconds(500);
  }
  delay(1000);

  digitalWrite(5,LOW);

  for(Index = 0; Index < 2000; Index++)
  {
    digitalWrite(2,HIGH);
    delayMicroseconds(500);
    digitalWrite(2,LOW);
    delayMicroseconds(500);
  }
  delay(1000);
}
