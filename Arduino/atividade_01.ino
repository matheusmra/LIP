void setup()
{
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  static bool LED = LOW; 

  if (digitalRead(7) == HIGH)
  {
    LED = !LED;
    digitalWrite(8, LED);
    delay(100); 
  }
}