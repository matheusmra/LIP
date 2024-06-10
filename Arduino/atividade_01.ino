//Alarme de intruso: crie um sistema de alarme simples no qual um LED acende quando um botão é pressionado e mantém-se aceso até que o botão seja pressionado novamente para desativá-lo
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