
const int botaoPin = 2; // Pino do botão
const int ledPin = 13; // Pino do LED


int contador = 0;
unsigned long tempoInicial = 0;

void setup()
{
  pinMode(botaoPin, INPUT);
  pinMode(ledPin, OUTPUT);

}

void loop()
{

  if (digitalRead(botaoPin) == HIGH)
  {

    if (contador == 0)
    {
      tempoInicial = millis();
    }

  
    contador++;
    delay(100);
  }


  if (millis() - tempoInicial >= 2000)
  {
  
    for (int i = 0; i < contador; i++)
    {
      digitalWrite(ledPin, HIGH);
      delay(500); 
      digitalWrite(ledPin, LOW);
      delay(500); 
    }

    
    contador = 0;
    tempoInicial = 0;
  }
}
