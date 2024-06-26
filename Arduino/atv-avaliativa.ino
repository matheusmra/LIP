const int potencio = A0;         
const int ledVerde = 4;      
const int ledAmarelo = 3;   
const int ledVermelho = 2;
const int bot = 1;

bool ligado = true;

void setup() {
  pinMode(potencio, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode (13, OUTPUT);
  pinMode (bot, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (ligado == true) {
    int potValue = analogRead(potencio);
    int temperatura = map(potValue, 0, 1023, 0, 50);
    Serial.print("A temperatura da piscina é: ");
    Serial.print(temperatura);
    Serial.println(" °C");

    if (temperatura >= 20 && temperatura <= 30) {
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVermelho , LOW);
    } else if (temperatura >= 31 && temperatura <= 35) {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, HIGH);
      digitalWrite(ledVermelho , LOW);
    } else if (temperatura > 35) {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVermelho , HIGH);
      tone(13, 200, 100);
      delay(200);
    } else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarelo, LOW);
      digitalWrite(ledVermelho , LOW);
    }
  } else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho , LOW);
  }

  delay(500);
}
