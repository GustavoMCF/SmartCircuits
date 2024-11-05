### Descrição do Projeto
Este projeto implementa um sistema de segurança com Arduino que permite criar, encriptar e verificar a força de uma senha utilizando LEDs e um display LCD I2C. O LED verde indica uma senha forte, o LED amarelo representa uma senha de força média, e o LED vermelho indica uma senha fraca. A senha é encriptada com uma criptografia simples para armazená-la temporariamente. A interface com o usuário é feita via serial, permitindo verificar e exibir a senha no LCD.

### Componentes Necessários
- Arduino Uno
- Display LCD I2C
- LEDs (Verde, Amarelo e Vermelho)
- Resistores para LEDs

### Funcionalidades
- **Criação de Senha**: Permite que o usuário defina uma senha personalizada.
- **Encriptação de Senha**: Realiza uma criptografia simples, somando +3 ao valor ASCII de cada caractere da senha.
- **Verificação de Força da Senha**: Avalia a complexidade da senha e indica sua força através de LEDs coloridos (verde para forte, amarelo para média e vermelho para fraca).
- **Exibição no LCD**: As mensagens de status e a senha (original ou encriptada) são exibidas no display LCD I2C.