### Descrição do Projeto
Este projeto permite controlar até cinco servos de um braço mecânico utilizando um joystick com Arduino. O botão do joystick alterna entre os servos, permitindo controlar cada um individualmente. O movimento no eixo Y do joystick ajusta o ângulo do servo selecionado, enquanto uma zona morta é configurada para evitar movimentação não intencional quando o joystick está no centro.

### Componentes Necessários
- Arduino Uno
- Braço Mecânico
- Joystick analógico com botão integrado
- Jumpers e cabos de conexão

### Funcionalidades
- **Controle Individual de Servos**: Alterna entre cinco servos do braço mecânico com o botão do joystick, permitindo ajuste de cada servo.
- **Movimento Preciso com Zona Morta**: Controla o servo selecionado com o eixo Y do joystick e evita movimentos não intencionais com uma zona morta.
- **Feedback Serial**: Exibe no Monitor Serial o servo atualmente selecionado e o ângulo de cada movimento, facilitando o monitoramento.