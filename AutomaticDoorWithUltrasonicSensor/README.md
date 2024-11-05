### Descrição do Projeto
Este projeto utiliza um Arduino para controlar a abertura e o fechamento automático de uma porta com base na proximidade detectada por um sensor ultrassônico. A sensibilidade de detecção é ajustada via potenciômetro, e um buzzer fornece feedback sonoro que varia em frequência e intervalo conforme a proximidade. 

### Componentes Necessários
- Arduino Uno
- Sensor Ultrassônico (HC-SR04)
- Servo motor para abertura/fechamento da porta
- Potenciômetro para ajuste da distância de detecção
- Buzzer para alerta sonoro
- Jumpers e cabos de conexão

### Funcionalidades
- **Abertura e Fechamento Automático**: A porta abre ao detectar aproximação e fecha quando não há presença próxima.
- **Ajuste de Sensibilidade**: Potenciômetro permite definir a distância para abrir a porta (de 5 a 100 cm).
- **Feedback Sonoro**: O buzzer emite sons de frequência e intervalo variáveis conforme a proximidade, indicando a detecção.
- **Log no Monitor Serial**: Exibe a distância medida, frequência, intervalo e duração do beep, além dos ajustes de abertura e fechamento.