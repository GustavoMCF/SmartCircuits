#include <Servo.h>

// Definição dos pinos
const int joyXPin = A0;       // Pino do eixo X do joystick
const int joyYPin = A1;       // Pino do eixo Y do joystick
const int buttonPin = 11;     // Pino do botão do joystick (SW)
const int servoPins[5] = {2, 3, 4, 5, 6};  // Pinos dos servos do braço

Servo servos[5];  // Array de 5 servos

const int deadzone = 30;  // Definindo a zona morta em torno de 512
int lastAngles[5] = {90, 90, 90, 90, 90};  // Última posição dos servos
int currentServo = 0;  // Índice do servo atualmente selecionado
int lastButtonState = HIGH;  // Estado anterior do botão

void setup() {
  // Iniciar os 5 servos
  for (int i = 0; i < 5; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(lastAngles[i]);  // Posição inicial (90 graus)
  }

  // Configurar o pino do botão como entrada com pull-up interno
  pinMode(buttonPin, INPUT_PULLUP);

  // Inicializa comunicação serial para depuração
  Serial.begin(9600);

  Serial.println("Sistema iniciado. Todos os servos na posição inicial (90 graus).");
}

void loop() {
  // Leitura dos valores do joystick (0 a 1023)
  int joyXValue = analogRead(joyXPin);
  int joyYValue = analogRead(joyYPin);

  // Leitura do estado do botão (LOW significa pressionado)
  int buttonState = digitalRead(buttonPin);

  // Se o botão for pressionado, alternar para o próximo servo
  if (buttonState == LOW && lastButtonState == HIGH) {
    currentServo = (currentServo + 1) % 5;  // Alterna entre os 5 servos
    Serial.println("Servo selecionado: " + String(currentServo + 1));
  }

  // Atualiza o estado anterior do botão
  lastButtonState = buttonState;

  // Controlar o servo atualmente selecionado usando o eixo Y do joystick
  if (abs(joyYValue - 512) > deadzone) {
    // Mapear o valor do eixo Y do joystick para o ângulo do servo selecionado (0 a 180)
    int newAngle = map(joyYValue, 0, 1023, 0, 180);
    if (newAngle != lastAngles[currentServo]) {  // Somente log se o ângulo mudou
      lastAngles[currentServo] = newAngle;
      servos[currentServo].write(newAngle);  // Mover o servo selecionado
      Serial.println("Servo " + String(currentServo + 1) + " movido para o ângulo: " + String(newAngle));
    }
  }

  // Pausa para evitar logs excessivos
  delay(200);
}
