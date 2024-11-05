### Descrição do Projeto
Este projeto permite controlar dois servos usando um joystick analógico com Arduino. O servo da direita responde ao movimento no eixo X do joystick, enquanto o servo da esquerda responde ao eixo Y. Um botão no joystick retorna ambos os servos à posição inicial de 90 graus. Uma zona morta é configurada para evitar movimentos indesejados quando o joystick está em sua posição central.

### Componentes Necessários
- Arduino Uno
- Dois servos
- Joystick analógico com botão integrado
- Jumpers e cabos de conexão

### Funcionalidades
- **Controle Independente dos Servos**: Controla o servo da direita pelo eixo X e o da esquerda pelo eixo Y do joystick.
- **Posição Inicial com Botão**: O botão do joystick, ao ser pressionado, retorna os servos à posição inicial (90 graus).
- **Zona Morta**: Evita movimentos dos servos quando o joystick está no centro, garantindo precisão no controle.
- **Feedback Serial**: Exibe no Monitor Serial o ângulo de cada servo e o estado do botão, facilitando o monitoramento e a depuração.