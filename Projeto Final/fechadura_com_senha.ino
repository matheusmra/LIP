// Importa biblioteca de componentes
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Define constantes para PIN
#define servoPin 12
#define redLEDPin 11
#define greenLEDPin 10

// Cria variáveis essenciais
String textInput = "";
String password = "1803";
const int passwordSize = password.length();
bool isResettingPassword = false;

// Cria mapa de teclas para o teclado
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define PINs do teclado
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Cria instância de componentes
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Servo servo;

// -------------------- MINHAS FUNÇÕES -------------------- //

// Muda posição do servo para aberto
void servoOpen() {
  for (int pos = 0; pos <= 90; pos += 10) servo.write(pos);
}

// Muda posição do servo para fechado
void servoClose() {
  for (int pos = 90; pos >= 0; pos -= 10) servo.write(pos);
}

// Limpa LCD e input de texto
void clearInput() {
  textInput = "";
  lcd.clear();
}

// Imprime caractere do teclado no LCD
void printKeyToLCD(char key) {
  lcd.setCursor(textInput.length(), 1);
  textInput += key;
  lcd.print(key);
}

// Apaga último caractere digitado no LCD
void deleteKeyFromLCD() {
  if(textInput == "") return;

  textInput.remove(textInput.length() - 1);
  lcd.setCursor(textInput.length(), 1);
  lcd.print(" ");
}

// Muda estado dos LEDs
void switchLEDs() {
  digitalWrite(redLEDPin, !digitalRead(redLEDPin));
  digitalWrite(greenLEDPin, !digitalRead(greenLEDPin));
}

// Define estado dos componentes ao destrancar a fechadura
void openLock() {
  lcd.clear();
  servoOpen();
  switchLEDs();
  lcd.print("Porta aberta");
}

// Define estado dos componentes ao trancar a fechadura
void closeLock(bool shouldForceClose = false) {
  // Verifica se deve trancar imediatamente
  if (!shouldForceClose) load("Fechando");

  lcd.clear();
  servoClose();     
  switchLEDs();
  lcd.print("Porta fechada");
  delay(1000);
  clearInput();
}

// Inicia modo de redefinição de senha
void startPasswordReset() {
  isResettingPassword = true;
  lcd.clear();
  lcd.print("Resetando senha");
  load("Carregando");
  clearInput();
}

// Espera N segundos para receber um comando
char waitForCommand(unsigned long waitInterval) {
  unsigned long startTime = millis();
  char key;

  // Espera até receber um comando específico
  // ou até atingir o tempo de espera definido
  while(millis() - startTime < waitInterval) {
    key = keypad.getKey();
    if (key == '#' || key == 'C') return key;
  }

  return NO_KEY;
}

// Imprime mensagem de carregamento
void load(char msg[]) {
  // Define linha de escrita do LCD para 1
  // e coluna de escrita para 0
  lcd.setCursor(0, 1);
  lcd.print(msg);
	
  // Imprime "." até preencher as colunas restantes do LCD
  for (int i = 0; i < 16 - strlen(msg); i++) {
    delay(1000);
    lcd.print(".");
  }
  delay(1000);
}

// ---------------- TERMINA MINHAS FUNÇÕES ---------------- //

void setup() {
  // Configura componentes Servo, LCD e LED
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  servo.attach(servoPin, 2000, 2400);
  lcd.begin(16, 2);

  // Define estado inicial dos componentes Servo e LED
  servoClose();
  digitalWrite(redLEDPin, HIGH);
  digitalWrite(greenLEDPin, LOW);

  // Imprime mensagens ao componente LCD
  lcd.print("Trava com senha");
  load("Carregando");
  lcd.clear();
}

void loop(){
  // Define linha de escrita do LCD para 0
  // e coluna de escrita para 0
  lcd.setCursor(0, 0);
  lcd.print(isResettingPassword ? "Nova senha:" : "Digite a senha:");

  // Espera até que uma tecla do teclado seja selecionada
  char inputKey = keypad.waitForKey();
	
  // Limpa texto digitado ao apertar tecla 'C'
  if (inputKey == 'C') clearInput();
  // Apaga última tecla digitada ao apertar tecla 'D'
  else if (inputKey == 'D') deleteKeyFromLCD();
  // Imprime tecla digitada
  else printKeyToLCD(inputKey);

  // Espera até que o total de caracteres digitados
  // seja o tamanho definido para a senha
  if (textInput.length() < passwordSize) return;

  // Redefine senha
  if (isResettingPassword) {
    password = textInput;
    isResettingPassword = false;
    return closeLock();
  }

  // Abre fechadura se a senha estiver correta
  if(textInput == password) {
    openLock();
    char command = waitForCommand(5000);
	
    // Ao receber comando, inicia modo de redefinição de senha
    if (command == '#') return startPasswordReset();
    // Fecha a fechadura de acordo com o comando recebido
    return closeLock(command == 'C');
  }

  // Se o usuário não estiver em modo de redefinição de senha
  // e a senha estiver incorreta
  // executa instruções abaixo
  lcd.clear();
  lcd.print("Senha errada");
  delay(1000);
  clearInput();
}