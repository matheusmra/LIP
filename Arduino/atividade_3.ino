// Simulação de semáforo com botão: crie um semáforo simples com três LEDs representando vermelho, amarelo e verde. Use um botão para simular o botão de pedestres. Quando o botão é pressionado, o semáforo deve mudar para a luz vermelha durante alguns segundos (para o pedestre passar)  antes de voltar ao ciclo normal.
void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT); // LED vermelho
  pinMode(12, OUTPUT); // LED amarelo
  pinMode(8, OUTPUT); // LED verde
}

void loop()
{
  static bool apertou = false; 

  if (digitalRead(2) == HIGH)
  {
    apertou = true;
  }

  if (apertou)
  {
    digitalWrite(8, LOW); 
    delay(2000);
    digitalWrite(12, HIGH); 
    delay(2000);
    digitalWrite(12, LOW); 
    digitalWrite(13, HIGH); 
    delay(6000);
    digitalWrite(13, LOW);
    digitalWrite(8, HIGH);
    apertou = false; 
  }
  {
    digitalWrite(8, HIGH); 
    
  }
}
