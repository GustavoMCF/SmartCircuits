#include <Servo.h>

// Definição dos pinos
const int joyXPin = A0;       // Pino do eixo X do joystick
const int joyYPin = A1;       // Pino do eixo Y do joystick
const int buttonPin = 11;     // Pino do botão do joystick (SW)
const int servoPinRight = 2;  // Pino de controle do servo para a direita
const int servoPinLeft = 4;   // Pino de controle do servo para a esquerda

Servo servoRight;  // Servo que gira para a direita
Servo servoLeft;   // Servo que gira para a esquerda

const int deadzone = 30;  // Definindo a zona morta em torno de 512

// Variáveis para armazenar a última posição dos servos
int lastAngleRight = 90;
int lastAngleLeft = 90;

// Variável para armazenar o estado anterior do botão
int lastButtonState = HIGH;

void setup() {
  // Iniciar os dois servos
  servoRight.attach(servoPinRight);
  servoLeft.attach(servoPinLeft);

  // Configurar o pino do botão como entrada com pull-up interno
  pinMode(buttonPin, INPUT_PULLUP);

  // Inicializa comunicação serial para depuração
  Serial.begin(9600);

  // Definir servos na posição inicial
  servoRight.write(lastAngleRight);
  servoLeft.write(lastAngleLeft);

  Serial.println("Sistema iniciado. Servos na posição inicial (90 graus).");
}

void loop() {
  // Leitura dos valores do joystick (0 a 1023)
  int joyXValue = analogRead(joyXPin);
  int joyYValue = analogRead(joyYPin);

  // Leitura do estado do botão (LOW significa pressionado)
  int buttonState = digitalRead(buttonPin);

  // Verificar se o estado do botão mudou
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Se o botão for pressionado, mover os servos para a posição inicial (90 graus)
    lastAngleRight = 90;
    lastAngleLeft = 90;
    servoRight.write(90);  // Posição inicial para o servo da direita
    servoLeft.write(90);   // Posição inicial para o servo da esquerda
    Serial.println("Botão pressionado - Servos voltaram para a posição inicial (90 graus).");
  } else {
    // Se o valor X estiver fora da zona morta
    if (abs(joyXValue - 512) > deadzone) {
      // Mapear o valor do eixo X do joystick para o ângulo do servo da direita (0 a 180)
      int newAngleRight = map(joyXValue, 0, 1023, 0, 180);
      if (newAngleRight != lastAngleRight) {  // Somente log se o ângulo mudou
        lastAngleRight = newAngleRight;
        servoRight.write(lastAngleRight);  // Gira o servo da direita
        Serial.println("Servo Direito movido para o ângulo: " + String(lastAngleRight));
      }
    }

    // Se o valor Y estiver fora da zona morta
    if (abs(joyYValue - 512) > deadzone) {
      // Mapear o valor do eixo Y do joystick para o ângulo do servo da esquerda (0 a 180)
      int newAngleLeft = map(joyYValue, 0, 1023, 0, 180);
      if (newAngleLeft != lastAngleLeft) {  // Somente log se o ângulo mudou
        lastAngleLeft = newAngleLeft;
        servoLeft.write(lastAngleLeft);    // Gira o servo da esquerda
        Serial.println("Servo Esquerdo movido para o ângulo: " + String(lastAngleLeft));
      }
    }
  }

  // Atualiza o estado anterior do botão
  lastButtonState = buttonState;

  // Pausa para evitar logs excessivos
  delay(500);
}