#include <Servo.h>

// Definição dos pinos
const int potPin = A0;       // Pino do potenciômetro
const int servoPinRight = 10; // Pino de controle do servo para a direita
const int servoPinLeft = 9; // Pino de controle do servo para a esquerda

Servo servoRight;  // Servo que gira para a direita
Servo servoLeft;   // Servo que gira para a esquerda

void setup() {
  // Iniciar os dois servos
  servoRight.attach(servoPinRight);
  servoLeft.attach(servoPinLeft);

  // Inicializa comunicação serial para depuração
  Serial.begin(9600);
}

void loop() {
  // Leitura do valor do potenciômetro (0 a 1023)
  int potValue = analogRead(potPin);

  // Verifica se o potenciômetro está acima ou abaixo do centro
  if (potValue > 550) {
    // Mapeia o valor do potenciômetro para o ângulo do servo da direita (90 a 180)
    int angleLeft = map(potValue, 550, 1023, 90, 180);
    servoLeft.write(angleLeft);  // Gira o servo da direita
    servoRight.write(90);           // Mantenha o servo esquerdo parado
    Serial.println("Servo Esquerdo Ativado - Ângulo: " + String(angleLeft));
  } 
  else if (potValue < 450) {
    // Mapeia o valor do potenciômetro para o ângulo do servo da esquerda (90 a 0)
    int angleRight = map(potValue, 0, 450, 0, 90);
    servoRight.write(angleRight);    // Gira o servo da esquerda
    servoLeft.write(90);          // Mantenha o servo direito parado
    Serial.println("Servo Direito Ativado - Ângulo: " + String(angleRight));
  }
  else {
    // Mantém ambos os servos parados no centro se o potenciômetro estiver no meio
    servoRight.write(90);  
    servoLeft.write(90);   
    Serial.println("Ambos os servos parados");
  }

  // Pausa para evitar logs excessivos
  delay(1000);
}