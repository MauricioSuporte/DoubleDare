# Placar de Pontuação com Arduino

Este projeto consiste em um placar de pontuação utilizando Arduino, inspirado no jogo "Passa ou Repassa", projetado para dois jogadores. O jogo inclui um sistema de pontuação, luzes de alarme e um botão de desativação para o juiz.

## Funcionalidades

- **Botões de Acionamento:** Cada time tem um botão de acionamento. Ao pressionar o botão, o jogo é iniciado para o respectivo time, ativando a sirene e a luz de alarme correspondente.
- **Sirene e Luz de Alarme:** Ao pressionar o botão de acionamento, a sirene e a luz de alarme do time correspondente são ativadas. Elas permanecem ligadas por um tempo pré-determinado (3 segundos) ou até que sejam desativadas pelo juiz.
- **Desativação do Alarme:** O juiz tem um botão para desativar a sirene e a luz de alarme quando necessário, seja após um tempo determinado ou se houver uma violação das regras do jogo.
- **Pontuação:** O juiz tem botões para adicionar pontos para cada time. Os pontos são exibidos em placares compostos de LEDs simples que formam displays de 7 segmentos, cada segmento com 3 LEDs.
- **Reset do Placar:** O juiz tem um botão para resetar os placares, zerando a pontuação de ambos os times.

## Sobre o Projeto

Neste projeto, optamos por criar um placar de pontuação utilizando Arduino e LEDs simples, em vez de usar um display de 7 segmentos pronto. Isso se deve às limitações de recursos na plataforma Tinkercad, onde só temos disponível o Arduino Uno e precisamos lidar com o número limitado de pinos digitais. Portanto, para contornar essa limitação, foi necessário usar 5 Arduinos no total: 1 mestre e 4 escravos, cada um responsável por controlar um dígito do placar. Essa abordagem nos permitiu criar um placar funcional dentro das restrições da plataforma de simulação.

## Circuito Elétrico

Abaixo está o circuito elétrico do projeto realizado na plataforma Tinkercad:

![Circuito Eletrico](https://github.com/MauricioSuporte/PassaOuRepassa/assets/50925332/543eafdd-ed48-45ed-ac93-cb642595dbc1)

## Contribuição

Sinta-se à vontade para contribuir com melhorias neste projeto. Você pode abrir problemas para relatar bugs ou solicitar novos recursos.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
