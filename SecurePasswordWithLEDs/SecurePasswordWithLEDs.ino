#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// Definições dos LEDs
#define LED_VERDE 4
#define LED_AMARELO 7
#define LED_VERMELHO 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

String senha = ""; // Armazenar a senha
String senhaEncriptada = ""; // Armazenar a senha encriptada

void setup() {
  // Inicializar LEDs
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  
  // Apagar todos os LEDs no início
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  
  // Inicializar Serial e LCD
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  // Exibir mensagem para criar senha
  lcd.setCursor(0, 0);
  lcd.print("Criar Senha:");
  Serial.println("Criar Senha:");
}

void loop() {
  // Solicitar a senha
  while (senha == "") {
    if (Serial.available() > 0) {
      senha = Serial.readStringUntil('\n'); // Lê até o Enter
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Senha Criada");
      Serial.println("Senha Criada");
      delay(3000);
      lcd.clear();
      
      // Mostrar opções
      mostrarMenuInicial();
    }
  }

  if (Serial.available() > 0) {
    char escolha = Serial.read(); // Lê a escolha do usuário
    
    if (escolha == '1') {
      solicitarSenhaParaEncriptar(); // Solicita a senha para encriptar
    } else if (escolha == '2') {
      solicitarSenhaParaDesencriptar(); // Solicita a senha para mostrar a senha original
    }
  }
}

void mostrarMenuInicial() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bem Vindo!");
  lcd.setCursor(0, 1);
  lcd.print("1) Encri 2) Desc");
  Serial.println("Bem Vindo! 1) Encri 2) Desc");
}

void solicitarSenhaParaEncriptar() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digite a senha:");
  Serial.println("Digite a senha:");
  
  String senhaDigitada = "";
  while (senhaDigitada == "") {
    if (Serial.available() > 0) {
      senhaDigitada = Serial.readStringUntil('\n'); // Lê até o Enter
    }
  }
  
  if (senhaDigitada == senha) {
    encriptarSenha();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Senha incorreta");
    Serial.println("Senha incorreta");
    delay(3000);
    mostrarMenuInicial();
  }
}

void solicitarSenhaParaDesencriptar() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digite a senha:");
  Serial.println("Digite a senha:");
  
  String senhaDigitada = "";
  while (senhaDigitada == "") {
    if (Serial.available() > 0) {
      senhaDigitada = Serial.readStringUntil('\n'); // Lê até o Enter
    }
  }
  
  if (senhaDigitada == senha) {
    mostrarSenhaOriginal();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Senha incorreta");
    Serial.println("Senha incorreta");
    delay(3000);
    mostrarMenuInicial();
  }
}

void mostrarSenhaOriginal() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Senha Original:");
  lcd.setCursor(0, 1);
  lcd.print(senha); // Exibe a senha original no LCD
  Serial.print("Senha Original: ");
  Serial.println(senha);

  verificarForca(senha); // Verifica a força da senha original

  delay(5000); // Espera 5 segundos para que o usuário veja a senha no LCD
  mostrarMenuInicial(); // Volta ao menu inicial
}

void encriptarSenha() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Encriptando...");
  Serial.println("Encriptando...");

  // Exemplo de criptografia simples
  senhaEncriptada = "";
  for (int i = 0; i < senha.length(); i++) {
    senhaEncriptada += char(senha[i] + 3); // Adiciona 3 ao valor ASCII de cada caractere
  }

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Encriptada:");
  lcd.setCursor(0, 1);
  lcd.print(senhaEncriptada);
  Serial.print("Encriptada: ");
  Serial.println(senhaEncriptada);

  verificarForca(senha); // Verifica a força da senha após a encriptação

  delay(5000); // Espera 5 segundos para que o usuário veja a senha encriptada no LCD
  mostrarMenuInicial(); // Volta ao menu inicial
}

void verificarForca(String senha) {
  bool temMaiuscula = false, temMinuscula = false, temNumero = false, temEspecial = false;
  
  for (int i = 0; i < senha.length(); i++) {
    char c = senha[i];
    if (isupper(c)) temMaiuscula = true;
    if (islower(c)) temMinuscula = true;
    if (isdigit(c)) temNumero = true;
    if (ispunct(c)) temEspecial = true;
  }

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  if (temMaiuscula && temMinuscula && temNumero && temEspecial) {
    digitalWrite(LED_VERDE, HIGH);  // Senha Forte
    Serial.println("Senha Forte: LED Verde ligado");
  } else if ((temMaiuscula && temMinuscula) || (temMaiuscula && temNumero) || (temMaiuscula && temEspecial) ||
             (temMinuscula && temNumero) || (temMinuscula && temEspecial) || (temNumero && temEspecial)) {
    digitalWrite(LED_AMARELO, HIGH);  // Senha Média
    Serial.println("Senha Média: LED Amarelo ligado");
  } else {
    digitalWrite(LED_VERMELHO, HIGH);  // Senha Fraca
    Serial.println("Senha Fraca: LED Vermelho ligado");
  }
}