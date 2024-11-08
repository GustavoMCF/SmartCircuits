#include <Servo.h>

const int trigPin = 9;     
const int echoPin = 10;    
const int potPin = A0;     
const int buzzerPin = 3;   
Servo servoMotor;          

long duration;
int distance;
int maxDistance;
const int BUZZER_BASE_FREQ = 500; // Frequência inicial do buzzer em Hz
unsigned long lastReadTime = 0;    // Armazena o tempo da última leitura
const int readInterval = 100;      // Intervalo de leitura em milissegundos

void setup() {
  servoMotor.attach(6);    
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Verifica se o intervalo de tempo passou
  if (millis() - lastReadTime >= readInterval) {
    lastReadTime = millis(); // Atualiza o último tempo de leitura

    // Ler o valor do potenciômetro e definir a distância máxima entre 10 e 100 cm
    maxDistance = map(analogRead(potPin), 0, 1023, 100, 10);

    // Enviar pulso para o sensor ultrassônico
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Calcular a duração do pulso de retorno
    duration = pulseIn(echoPin, HIGH);

    // Calcular a distância em centímetros
    distance = duration * 0.034 / 2;

    // Verificar se o objeto está dentro da distância máxima ajustada
    if (distance > 0 && distance <= maxDistance) {
      // Ajuste proporcional para o ângulo do servo, com base em maxDistance
      int servoAngle = map(distance, 0, maxDistance, 180, 0);
      servoAngle = constrain(servoAngle, 0, 180); // Limita entre 0 e 180 graus
      servoMotor.write(servoAngle);

      // Calcular frequência do buzzer usando a constante de base e distância direta
      int buzzerFrequency = BUZZER_BASE_FREQ + (int)((2000 - BUZZER_BASE_FREQ) * ((float)(maxDistance - distance) / maxDistance));
      buzzerFrequency = constrain(buzzerFrequency, BUZZER_BASE_FREQ, 2000); // Limita a frequência entre 500 e 2000 Hz
      tone(buzzerPin, buzzerFrequency, 100);

      // Exibir informações no Serial Monitor
      Serial.print("Distância: ");
      Serial.print(distance);
      Serial.print(" cm | Ângulo do Servo: ");
      Serial.print(servoAngle);
      Serial.print("° | Frequência do Buzzer: ");
      Serial.println(buzzerFrequency);
    } else {
      // Quando fora do alcance, reseta o servo e o buzzer
      servoMotor.write(0);
      noTone(buzzerPin);
    }
  }
}