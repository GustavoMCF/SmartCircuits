#include <Servo.h>

const int potPin = A0;    // Pino do potenciômetro
const int servoPin = 9;   // Pino de controle do servo
Servo myServo;            // Cria o objeto Servo

void setup() {
  // Iniciar o servo
  myServo.attach(servoPin);
  myServo.write(90);  // Inicializa o servo na posição central (90 graus)

  // Inicializa comunicação serial para depuração
  Serial.begin(9600);
}

void loop() {
  // Leitura do valor do potenciômetro (0 a 1023)
  int potValue = analogRead(potPin);

  // Mapear o valor do potenciômetro para o ângulo do servo (0 a 180)
  int angle = map(potValue, 0, 1023, 0, 180);

  // Mover o servo para o ângulo correspondente
  myServo.write(angle);

  // Exibir informações úteis no Monitor Serial a cada 500ms
  Serial.print("Potenciômetro: ");
  Serial.print(potValue);
  Serial.print(" | Ângulo do servo: ");
  Serial.println(angle);

  // Pausar para evitar logs excessivos
  delay(500);