#include <Servo.h>

// Definição dos pinos
const int trigPin = 8;          // Pino Trig do sensor ultrassônico
const int echoPin = 7;          // Pino Echo do sensor ultrassônico
const int potPin = A0;          // Pino do potenciômetro para ajuste de sensibilidade
const int buzzerPin = 6;        // Pino do buzzer
const int servoPin = 9;         // Pino do servo

Servo servo;                    // Objeto Servo

// Variáveis de controle da porta
int openDistance;               // Distância em cm para a porta abrir (controlada pelo potenciômetro)
int closeDistance;              // Distância em cm para a porta fechar (ajustado automaticamente)
const int margemHisterese = 5;  // Margem de segurança para estabilizar a detecção
bool portaAberta = false;       // Estado da porta (fechada por padrão)
long lastLogTime = 0;           // Tempo da última atualização do log

void setup() {
  // Configuração dos pinos
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  servo.attach(servoPin);

  // Inicialização do servo na posição fechada
  servo.write(0);  // Porta fechada
  Serial.begin(9600);

  Serial.println("Sistema inicializado. Porta fechada.");
  Serial.println("--------------------------------------");
}

void loop() {
  // Leitura do valor do potenciômetro para ajustar as distâncias de detecção
  openDistance = map(analogRead(potPin), 0, 1023, 5, 100);   // Ajuste de 5 a 100 cm
  closeDistance = openDistance + 10;                         // closeDistance é sempre 10 cm maior

  // Cálculo da distância medida pelo sensor ultrassônico
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Mapeamento Invertido: Quanto menor a distância, mais rápido e mais alto o som
  int beepFrequency = map(distance, closeDistance, openDistance, 500, 4000); // Frequência alta com proximidade
  beepFrequency = constrain(beepFrequency, 500, 4000); // Limitar frequência entre 500 Hz e 4000 Hz
  int beepInterval = map(distance, closeDistance, openDistance, 1000, 100);  // Intervalo rápido com proximidade
  beepInterval = constrain(beepInterval, 100, 1000); // Limitar intervalo entre 100 ms e 1000 ms
  
  // Ajuste de duração do beep baseado na proximidade
  int beepDuration = map(distance, openDistance, closeDistance, 50, 200); // Duração maior com proximidade
  beepDuration = constrain(beepDuration, 50, 200); // Limitar duração entre 50 ms e 200 ms

  // Condição para abrir a porta com histerese
  if (distance < (openDistance - margemHisterese) && !portaAberta) {
    servo.write(90);  // Abrir a porta
    portaAberta = true;
    Serial.println("Aproximação detectada. Abrindo porta...");
  }
  // Condição para fechar a porta com histerese
  else if (distance > (closeDistance + margemHisterese) && portaAberta) {
    servo.write(0);  // Fechar a porta
    portaAberta = false;
    Serial.println("Distância suficiente detectada. Fechando porta...");
  }

  // Controle do Buzzer enquanto a porta está aberta e dentro da faixa
  if (portaAberta && distance <= closeDistance) {
    tone(buzzerPin, beepFrequency); // Som do buzzer aumenta conforme proximidade
    delay(beepDuration);            // Duração do beep ajustado pela proximidade
    noTone(buzzerPin);              // Parar o som
    delay(beepInterval);            // Intervalo entre os beeps proporcional à distância
  } else {
    noTone(buzzerPin);  // Desliga o som quando fora da faixa ou porta fechada
  }

  // Atualização de log a cada 2 segundos
  if (millis() - lastLogTime >= 2000) {
    Serial.print("Distância medida: ");
    Serial.print(distance);
    Serial.print(" cm | Frequência do Buzzer: ");
    Serial.print(beepFrequency);
    Serial.print(" Hz | Intervalo de Beep: ");
    Serial.print(beepInterval);
    Serial.print(" ms | Duração do Beep: ");
    Serial.print(beepDuration);
    Serial.println(" ms");
    Serial.print("Ajuste de Abertura: ");
    Serial.print(openDistance);
    Serial.print(" cm | Ajuste de Fechamento: ");
    Serial.print(closeDistance);
    Serial.println(" cm");
    Serial.println("--------------------------------------");
    lastLogTime = millis();
  }
  
  // Pausa para evitar leituras excessivamente rápidas
  delay(200);
}
