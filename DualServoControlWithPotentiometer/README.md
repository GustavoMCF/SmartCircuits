### Descrição do Projeto
Este projeto controla dois servos usando um potenciômetro com Arduino. Dependendo da posição do potenciômetro, um dos servos se movimenta enquanto o outro permanece parado. A interface serial exibe o ângulo de cada servo e o estado atual, permitindo o monitoramento e ajuste preciso.

### Componentes Necessários
- Arduino Uno
- Dois servos
- Potenciômetro
- Jumpers e cabos de conexão

### Funcionalidades
- **Controle de Servos**: Movimenta o servo da direita quando o potenciômetro está acima do centro e o da esquerda quando está abaixo. Se o potenciômetro estiver no meio, ambos os servos permanecem na posição central.
- **Feedback Serial**: Exibe o ângulo atual de cada servo e o estado no Monitor Serial, facilitando a depuração e o acompanhamento dos movimentos.