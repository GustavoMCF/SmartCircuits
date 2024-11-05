### Descrição do Projeto
Este projeto utiliza um sensor ultrassônico, um servo motor e um buzzer com um Arduino Uno para medir a distância de objetos e responder de acordo com a proximidade. A distância máxima de detecção é ajustada por um potenciômetro: quanto maior o valor do potenciômetro, maior a distância máxima de operação. O servo motor ajusta sua posição com base na distância, e o buzzer emite sons cuja frequência aumenta à medida que o objeto se aproxima.

### Componentes Necessários
- Arduino Uno
- Sensor Ultrassônico (HC-SR04)
- Servo Motor (SG90 ou similar)
- Buzzer
- Potenciômetro
- Protoboard
- Jumpers

### Funcionalidades
- **Ajuste de Distância**: O potenciômetro permite ajustar a distância máxima de detecção entre 10 cm e 100 cm.
- **Controle de Servo**: O servo motor se move para diferentes posições conforme a distância do objeto.
- **Alerta Sonoro**: O buzzer emite sons de frequência variável que aumentam conforme o objeto se aproxima.