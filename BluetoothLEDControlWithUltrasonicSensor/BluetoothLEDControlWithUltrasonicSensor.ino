#include <Dabble.h>          // Biblioteca para integração com o app Dabble
#include <SoftwareSerial.h>  // Biblioteca para comunicação serial de software

// Configuração do módulo Bluetooth nos pinos 10 (RX) e 11 (TX)
SoftwareSerial BTSerial(10, 11);

const int ledPin = 13;       // Pino do LED
const int trigPin = 8;       // Pino Trig do sensor ultrassônico
const int echoPin = 7;       // Pino Echo do sensor ultrassônico
long distancia;              // Variável para armazenar a distância calculada
unsigned long lastReadTime = 0; // Tempo da última leitura de distância
const long intervalo = 4000;    // Intervalo de leitura do sensor (4 segundos)

void setup() {
  BTSerial.begin(9600);       // Inicializa o Bluetooth
  Serial.begin(9600);         // Inicializa o Monitor Serial para depuração

  // Configuração dos pinos
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializa o Dabble
  Dabble.begin(BTSerial);

  // Mensagem de inicialização
  Serial.println("Sistema pronto. Use o Dabble para controlar o LED e monitorar a distância.");
}

void loop() {
  // Processa a entrada do Dabble
  Dabble.processInput();

  // Verifica se o Dabble enviou dados para o Arduino
  if (Terminal.available()) {
    String comando = Terminal.readString(); // Lê o comando recebido
    
    // Filtra comandos para evitar ruídos e processa "1" e "0"
    if (comando == "1") {
      digitalWrite(ledPin, HIGH); // Liga o LED
      Serial.println("LED ON");
      Terminal.println("LED Ligado | Distância: " + String(distancia) + " cm"); // Envia status e distância em uma linha
    } 
    else if (comando == "0") {
      digitalWrite(ledPin, LOW);  // Desliga o LED
      Serial.println("LED OFF");
      Terminal.println("LED Desligado | Distância: " + String(distancia) + " cm"); // Envia status e distância em uma linha
    }
  }

  // Verifica se é hora de fazer uma nova leitura do sensor ultrassônico
  unsigned long currentTime = millis();
  if (currentTime - lastReadTime >= intervalo) {
    distancia = medirDistancia();
    lastReadTime = currentTime;

    // Exibe a distância no Monitor Serial
    Serial.print("Distância medida: ");
    Serial.print(distancia);
    Serial.println(" cm");

    // Envia a distância para o terminal do Dabble em uma linha
    Terminal.println("Status: " + String((digitalRead(ledPin) == HIGH) ? "LED Ligado" : "LED Desligado") + " | Distância: " + String(distancia) + " cm");
  }

  delay(100); // Atraso pequeno para evitar sobrecarga
}

// Função para medir a distância com o sensor ultrassônico
long medirDistancia() {
  // Gera um pulso ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calcula a duração do pulso e converte para centímetros
  long duracao = pulseIn(echoPin, HIGH);
  long distanciaCalculada = duracao * 0.034 / 2;
  return distanciaCalculada;
}
