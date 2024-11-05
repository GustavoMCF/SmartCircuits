### Descrição do Projeto
Este projeto permite controlar um LED via Bluetooth utilizando o aplicativo Dabble e monitorar a distância de objetos próximos com um sensor ultrassônico. O LED pode ser ligado ou desligado por comandos recebidos via Bluetooth, enquanto a distância medida é exibida no aplicativo Dabble e no Monitor Serial do Arduino. Um intervalo de leitura é configurado para evitar leituras constantes.

### Componentes Necessários
- Arduino Uno
- Módulo Bluetooth (HC-05)
- Sensor Ultrassônico (HC-SR04)
- LED
- Resistor para o LED
- Jumpers e cabos de conexão

### Funcionalidades
- **Controle de LED via Bluetooth**: Liga e desliga o LED com comandos do aplicativo Dabble (1 para ligar, 0 para desligar).
- **Monitoramento de Distância**: Mede a distância de objetos próximos e envia o valor para o aplicativo Dabble e para o Monitor Serial.
- **Integração com Dabble**: O aplicativo Dabble permite o controle remoto e visualização de status do LED e da distância medida.