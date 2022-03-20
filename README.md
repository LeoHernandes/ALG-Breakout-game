# Breakout no prompt de comando

![Menu](https://user-images.githubusercontent.com/72423032/158039306-6c4a9271-c790-4f8e-be37-877eb17d7f97.png)

Jogo feito completamente no prompt de comando em C inspirado no clássico Breakout de Atari. Foi usada a biblioteca [conio2.h](https://pt.osdn.net/projects/sfnet_hlanguage/downloads/Source/include/conio2.h/) para construir toda a interface do jogo.

## Como o jogo funciona?

Quando o jogo é iniciado, temos opções de dificuldade:

![dificuldade](https://user-images.githubusercontent.com/72423032/159183507-0935179d-359e-4096-b73f-be5f769ba2b3.png)

Dependendo da escolha, são afetadas a velocidade da bolinha no jogo, a largura da palheta que ricocheteia a bolinha e a quantidade de pontos ganhos a cada tijolo quebrado.

Logo após é requisitado o nome do jogador para salvar sua pontuação futuramente:

![nome](https://user-images.githubusercontent.com/72423032/159183773-3b954073-f35a-45a5-93b7-ace6a927ea20.png)

Iniciada a primeira fase, temos na parte mais superior um guia de comandos possíveis durante o jogo. Abaixo temos a tela onde o jogo é renderizado e no canto direito temos várias informações, listadas de baixo para cima:

* Vidas
* Pontuação atual no jogo
* Tabela de pontuações salvas que é atualizada em tempo real, mostrando no máximo 5 jogadores por vez
* Informações gerais sobre o projeto
  
![jogo1](https://user-images.githubusercontent.com/72423032/159183811-f26a8f85-17ef-4c01-ba9f-684d3a604e1d.png)

Cada tijolo, dependendo da sua cor, necessita de um número diferente de batidas para ser quebrado:
* Tijolo amarelo claro: 1 batida
* Tijolo vermelho claro: 2 batidas
* Tijolo vermelho escuro: 3 batidas

No total o jogo possui 3 fases e cada uma possui uma configuração diferente de tijolos, a fim de dificultar o jogo. Entretanto o jogador possui uma chance de receber bônus quando quebra um tijolo. Os bônus são:
* Aumentar a largura da palheta
* Ganhar uma vida adicional
* Ganhar um multiplicador de pontos

O jogo pode ser salvo a qualquer momento, basta escolher um nome para o arquivo em que o jogo vai ser salvo. Quando o jogador quiser carregar um jogo salvo, precisa inserir o exato nome escolhido quando salvou o jogo.

É possível ver a tabela de pontuação também pela opção do menu:

![pontuacoes](https://user-images.githubusercontent.com/72423032/159184498-6efb152c-fef2-48d0-a8b9-2c4a187bfc47.png)

## Créditos

![credito](https://user-images.githubusercontent.com/72423032/159184529-00ad1178-da16-4e58-93b7-9a6f00522ef4.png)


