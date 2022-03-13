#include <stdio.h>
#include <windows.h>
#include <conio2.h>
#include <time.h>
#include <stdlib.h>
#include "Estruturas_Constantes.h"

void esconde_cursor()
//função para nao aparecer o cursor
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void printa_creditos_ingame()
//printa os creditos do jogo no canto inferior direito do jogo
{
    gotoxy(XFIM + 2, ALTURA_DIVISAO + 10);
    printf("Semestre 2020/1 - INF1202");
    gotoxy(XFIM + 2, ALTURA_DIVISAO + 11);
    printf("Algoritmos e Programacao");
    gotoxy(XFIM + 2, ALTURA_DIVISAO + 12);
    printf("Turma D");
    gotoxy(XFIM + 2, ALTURA_DIVISAO + 13);
    printf("Professora Mara Abel");
    gotoxy(XFIM + 2, ALTURA_DIVISAO + 14);
    printf("Professor Fernando");
    gotoxy(XFIM + 2, ALTURA_DIVISAO + 16);
    printf("Programadores:");
    gotoxy(XFIM + 2, ALTURA_DIVISAO + 17);
    printf("Leo Hernandes de Vasconcelos");
    gotoxy(XFIM + 2, ALTURA_DIVISAO + 18);
    printf("Nikolas Padao Schuster");
}

void desenha_janela(FASE level)
//desenha a moldura/limite da area jogavel
{
    int i;

    textcolor(level.cor);
    //uso do gotoxy ao inves de putchxy, para poder colocar os códigos da tabela ASCII
    cputsxy(XINFO, YINFO, "(C)arregar um jogo     |    (P)ausar     |    (ESC)Sair     |     ESPACO para comecar");
    gotoxy(XINI, YINI);
    printf("%c", BORDA_SE); //borda superior esquerda
    gotoxy(XFIM, YINI);
    printf("%c", BORDA_SD); //borda superior direita
    gotoxy(XINI, YFIM);
    printf("%c", BORDA_IE); //borda inferior esquerda
    gotoxy(XFIM, YFIM);
    printf("%c", BORDA_ID); //borda inferior direita

    gotoxy(XINI + 1, YINI);    //vai pra linha superior
    for(i = XINI + 1; i < XFIM; i++)
        printf("%c", BARRA_H);

    gotoxy(XINI + 1, YFIM);    //vai pra linha inferior
    for(i = XINI + 1; i < XFIM; i++)
        printf("%c", BARRA_H);

    for(i = YINI + 1; i < YFIM; i++)
    {
        gotoxy(XINI, i); //vai pra coluna esquerda
        printf("%c", BARRA_V);
    }

    for(i = YINI + 1; i < YFIM; i++)
    {
        gotoxy(XFIM, i); //vai pra coluna direita
        printf("%c", BARRA_V);
    }
}

void desenha_janela_informacoes(FASE level)
//desenha a janela de informacoes adicionais na lateral direita
{
    int i;
    textcolor(level.cor);

    gotoxy(XFIM + JANELAINFO_LARGURA, YINI);
    printf("%c", BORDA_SD); //borda superior direita

    gotoxy(XFIM + JANELAINFO_LARGURA, YFIM);
    printf("%c", BORDA_ID); //borda inferior direita

    gotoxy(XFIM + 1, YINI);    //vai pra linha superior
    for(i = (XFIM + 1); i < XFIM + JANELAINFO_LARGURA; i++)
        printf("%c", BARRA_H);

    gotoxy(XFIM + 1, YFIM);    //vai pra linha inferior
    for(i = XFIM + 1; i < XFIM + JANELAINFO_LARGURA; i++)
        printf("%c", BARRA_H);

    for(i = YINI + 1; i < YFIM; i++)
    {
        gotoxy(XFIM + JANELAINFO_LARGURA, i); //vai pra coluna direita
        printf("%c", BARRA_V);
    }

    gotoxy(XFIM + 1, ALTURA_DIVISAO );
    for(i = XFIM + 1; i < XFIM + JANELAINFO_LARGURA; i++)//faz a divisao da janela de info
        printf("%c", BARRA_H);

    gotoxy(XFIM + 1, ALTURA_DIVISAO2 );
    for(i = XFIM + 1; i < XFIM + JANELAINFO_LARGURA; i++)//faz a outra divisao da janela de info
        printf("%c", BARRA_H);

    printa_creditos_ingame();
}

void printa_palheta(PALHETA pal)
//desenha a palheta
{
    int i = pal.ponto1.x;

    textcolor(pal.cor);
    gotoxy(pal.ponto1.x, pal.ponto1.y);
    //while evita printar a palheta fora da moldura
    //no caso especifico em que o player ganha bonus
    //de aumentar a palheta enquanto ela está colada na moldura
    while(i <= pal.ponto2.x && i < XFIM)
    {
        printf("%c", SIMBOLO_PALHETA);
        i++;
    }
}

void printa_bolinha(BOLA bol)
//desenha bolinha com caracter especial
{
    textcolor(bol.cor);
    gotoxy(bol.posicao.x, bol.posicao.y);
    printf("%c", SIMBOLO_BOLINHA);
}

void escolhe_cor_tijolo(TIJOLO tij)
// escolhe a cor do tijolo de acordo com a quantidade de batidas necessarias para destrui-lo
{
    switch(tij.vidas)
    {
    case 1:
        textcolor(YELLOW);
        break;
    case 2:
        textcolor(LIGHTRED);
        break;
    case 3:
        textcolor(RED);
    }
}

void desenha_tijolo(TIJOLO *tij)
//desenha um unico tijolo nas coordenadas dadas
{
    int i, j;

    if((tij->ponto2.x < XFIM) && (tij->ponto1.x > XINI) && (tij->ponto1.y > YINI) && (tij->ponto2.y < ALTURA_PALHETA))
    {
        escolhe_cor_tijolo(*tij);
        for(j = tij->ponto1.y; j <= tij->ponto2.y; j++)
            for(i = tij->ponto1.x; i <= tij->ponto2.x; i++)
            {
                gotoxy(i, j);
                printf("%c", SIMBOLO_TIJOLO);
            }
        textcolor(WHITE);
    }
    else
    //se o tijolo não pode ser printado na moldura
    //é necessario zerar as coord dele pra não ter um tijolo invisivel colidindo
    {
        // zera coordenadas
        tij->ponto1.x = 0;
        tij->ponto1.y = 0;
        tij->ponto2.x = 0;
        tij->ponto2.y = 0;
        // atualiza o status do tijolo
        tij->status = 2;
    }
}

void desenha_tijolos(TIJOLO listatijolo[])
//desenha todos os tijolos da fase com o vetor de tijolos
{
    int i;

    for(i = 0; i < NUMTIJ; i++)
        //se n tiver sido destruido ainda
        if(listatijolo[i].status == 1)
            desenha_tijolo(&listatijolo[i]);
}

void printa_pontos(JOGADOR jog)
//printa na janela de informacoes a quantidade de
//pontos do jogador
{
    textcolor(WHITE);
    gotoxy(XPONTOS, ALTURA_DIVISAO2 + 2);
    printf("Pontuacao: %d", jog.pontos);
}

void printa_vidas(JOGADOR jog)
//printa na janela de informacoes a quantidade de
//vidas do jogador
{
    int i;

    textcolor(WHITE);
    gotoxy(XPONTOS, ALTURA_DIVISAO2 + 1);
    printf("Vidas:          "); //espacos adicionais para tirar vidas perdidas
    gotoxy(XPONTOS + 7, ALTURA_DIVISAO2 + 1);
    for(i=0; i < jog.vidas; i++) //printa o simbolo de coracao pra mostrar as vidas
        printf("%c", CORACAO);
}

void apaga_tijolo(TIJOLO tij)
//apaga o tijolo da posicao dada
{
    int x, y;

    for(y = tij.ponto1.y; y <= tij.ponto2.y; y++)
        for(x = tij.ponto1.x; x <= tij.ponto2.x; x++)
            putchxy(x, y,' ');
}

void desce_lista(int i, JOGADOR lista[])
// desloca para direita no vetor todos os elementos depois do indice "i"
{
    int j;
    for(j = MAX_JOGADORES - 1; j > i; j--)
    {
        lista[j] = lista[j - 1];
    }
}

void sobe_lista(int i, JOGADOR lista[])
//desloca para direita todos os elementos no vetor comecando no indice "i"
{
    while(i < MAX_JOGADORES)
    {
        lista[i] = lista[i+1];
        i++;
    }
}

int temNomeIgual(JOGADOR jog, JOGADOR lista[])
//devolve a posicao na lista em que o elemento tem o mesmo nome do jogador dado,
//devolve -1 se nao encontrar
{
    int pos = 0;

    while(pos < MAX_JOGADORES)
    {
        if(!strcmp(jog.nome, lista[pos].nome))
            //retorna a posicao em que o nome e' igual
            return pos;
        pos++;
    }
    //retorna -1 se nao encontrou nenhum nome igual
    return -1;
}

void inserirJogador(int i, JOGADOR jog, JOGADOR lista[])
//insere, se possivel, o jogador na lista de forma que ela fique ordenada
{
    int posicao;
    JOGADOR vazio = {};

    posicao = temNomeIgual(jog, lista);
    //se encontrou nome igual
    if(posicao >= 0)
    {
        //se fez mais pontos que anteriormente
        if(jog.pontos > lista[posicao].pontos)
        {
            //apaga registro anterior
            lista[posicao] = vazio;
            sobe_lista( posicao, lista);
            //insere o nome no lugar correto
            desce_lista( i, lista);
            lista[i].pontos = jog.pontos;
            strcpy( lista[i].nome, jog.nome);
        }
    }
    //se nao tem nome igual, apenas insere
    else
    {
        desce_lista( i, lista);
        lista[i].pontos = jog.pontos;
        strcpy(lista[i].nome, jog.nome);
    }
}

void OrdenaListaJogadores(JOGADOR jog, JOGADOR lista[])
//procura se tem lugar para colocar o novo jogador e insere de forma a deixar ordenada a lista
{
    int i = 0;
    int parar = 0;

    do
    {
        if(jog.pontos > lista[i].pontos)
        {
            inserirJogador(i, jog, lista);
            parar = 1;
        }
        i++;
    }
    while(!parar && (i < 5));
}

void MostraListaJogadores(JOGADOR jog, JOGADOR score[])
//mostra todas as pontuacoes dos jogadores e a pontuacao do jogador atual
//caso ele nao esteja ainda na lista de pontuacao
{
    int i = 0;
    gotoxy(XPONTOS, ALTURA_DIVISAO + 1);
    printf("PONTUACOES:");
    while(score[i].pontos != 0 && i < MAX_JOGADORES)
    {
        gotoxy(XPONTOS, ALTURA_DIVISAO + 2 + i);
        printf("%20s - %6d", score[i].nome, score[i].pontos);
        i++;
    }
    //se nao tiver nome igual
    if(temNomeIgual(jog, score) == -1)
    {
        //printa o jogador atual abaixo
        gotoxy(XPONTOS, ALTURA_DIVISAO + 2 + i);
        printf("%20s - %6d", jog.nome, jog.pontos);
    }
}

void destroi_tijolo(int indicetijolo, TIJOLO listatijolo[], JOGADOR *jog, JOGADOR score[], FASE level[])
//tira vida do tijolo, apaga ele se precisar e atualiza a pontuacao do jogador
{
    if(listatijolo[indicetijolo].vidas > 1)
    {
        listatijolo[indicetijolo].vidas--;
        desenha_tijolo(&listatijolo[indicetijolo]);
    }
    else
    {
        apaga_tijolo(listatijolo[indicetijolo]);
        // zera coordenadas
        listatijolo[indicetijolo].ponto1.x = 0;
        listatijolo[indicetijolo].ponto1.y = 0;
        listatijolo[indicetijolo].ponto2.x = 0;
        listatijolo[indicetijolo].ponto2.y = 0;
        // atualiza o status do tijolo
        listatijolo[indicetijolo].status = 2;
        // atualiza pontuacao do jogador
        jog->pontos += (level->multiplicador * listatijolo[indicetijolo].pontos) + listatijolo[indicetijolo].bonus;
        printa_pontos(*jog);
        OrdenaListaJogadores(*jog, score);
        MostraListaJogadores(*jog, score);
    }
}

void limpa_erro_arquivo()
//coloca brancos na parte abaixo da moldura
//para apagar os erros de arquivos
{
    int i;

    gotoxy(XINI, YFIM + 1);
    for(i = XINI; i <= XFIM; i++)
    {
        printf(" ");
    }
}

int printa_game_over()
//carrega o arquivo que contem o texto de gameover e printa na tela
//retorna 0 se houve erro, retorna 1 se foi feito com sucesso
{
    FILE *arq;
    char linha[STRINGAO];

    if((arq = fopen("gameover.txt","r")) == NULL)
    {
        limpa_erro_arquivo();
        cputsxy(XINI + 1, YFIM + 1, "*** ERRO AO ABRIR O ARQUIVO DE GAME-OVER ***");
        return 0;
    }

    while(!feof(arq))
    {
        if(fgets(linha, sizeof(linha), arq) == NULL)
        {
            limpa_erro_arquivo();
            cputsxy(XINI + 1, YFIM + 1, "*** ERRO AO LER O ARQUIVO DE GAME-OVER ***");
            fclose(arq);
            return 0;
        }
        else
        {
            printf("%s", linha);
        }
    }

    fclose(arq);
    return 1;
}

void animacao_game_over()
//mostar o texto de game-over animado quando o jogador perde
{
    char tecla = 0;
    textcolor(LIGHTRED);

    do
    {
        clrscr();
        Sleep(800);
        if(kbhit())
            tecla = getch();
        printa_game_over();
        printf("\n\n\n\nPRESSIONE 'ENTER' PARA CONTINUAR\n");
        Sleep(1200);
        if(kbhit())
            tecla = getch();
    }
    while(tecla != ENTER);
}

void limpa_palheta(PALHETA pal)
//limpa o lugar onde a palheta esta
{
    int i = pal.ponto1.x;

    gotoxy(pal.ponto1.x, pal.ponto1.y);
    while(i <= pal.ponto2.x && i < XFIM)
    {
        putch(' ');
        i++;
    }
}

int bonus()
//sorteia a chance do jogador de ganhar um bonus
//devolve 0 se nao ganhou e 1 se ganhou bonus
{
    int chance;

    chance = (int)(rand() / (double)RAND_MAX * (101));
    if(chance < PROB_BONUS) //chance de 5% para ganhar o bonus
        return 1;
    return 0;
}

void info_bonus(char *bonus)
//dada um texto, printa no local que informa o bonus adquirido
{
    gotoxy(XFIM + 2, ALTURA_DIVISAO2 + 4);
    textcolor(YELLOW);
    puts(bonus);
}

void limpa_bonus()
//limpa o lugar do texto do bonus
{
    int i;

    gotoxy(XFIM + 2, ALTURA_DIVISAO2 + 4);
    for(i = 1; i < JANELAINFO_LARGURA - 1; i++)
        printf(" ");
}

void aumenta_pontos(TIJOLO listaTijolos[])
//aumenta a pontuacao bonus dos tijolos ate um limite de 40 pts
{
    int tijolo;
    //verifica a pontuacao só de um elemento, pois todos sempre sao iguais
    if(listaTijolos[0].bonus < 40)
    {
        for(tijolo = 0; tijolo < NUMTIJ; tijolo++)
        {
            listaTijolos[tijolo].bonus += 10;
        }
        limpa_bonus();
        info_bonus("MAIS PONTOS");
    }
}

void aumenta_palheta(PALHETA *pal, JOGADOR jog)
//aumenta o tamanho da palheta em 4 unidades
{
    if(jog.bonuspalheta == 0)
    //se o tamanho atual ainda nao foi aumentado
    {
        pal->ponto2.x += 4;
        printa_palheta(*pal);
        limpa_bonus();
        info_bonus("PALHETA MAIOR");
    }
}

void aumenta_vida(JOGADOR *jog)
//aumenta a vida do jogador ate um limite de 9 vidas
{
    if(jog->vidas < 9)
    {
        jog->vidas++;
        limpa_bonus();
        info_bonus("+1 VIDA");
        printa_vidas(*jog);
    }
}

void tira_bonus_palheta(PALHETA *pal, JOGADOR jog)
//tira o bonus do tamanho da palheta, retornando
//para o tamanho anterior
{
    //voltar ao normal o tamanho
    limpa_palheta(*pal);
    pal->ponto2.x -= 4;

    printa_palheta(*pal);
    limpa_bonus();
}

void tira_bonus_pontos(TIJOLO listaTijolos[])
//retorna o bonus de pontuacao para zero
{
    int tijolo;
    for(tijolo = 0; tijolo < NUMTIJ; tijolo++)
    {
        listaTijolos[tijolo].bonus = 0;
    }
    limpa_bonus();
}

void gera_bonus(TIJOLO listaTijolos[], PALHETA *pal, JOGADOR *jog, FASE fase)
//escolhe aleatoriamente um bonus para o jogador
{
    int randomBonus = (int)(rand() / (double)RAND_MAX * (3));

    switch(randomBonus)
    {
    case 0:
        aumenta_pontos(listaTijolos);
        jog->bonusponto = 1;
        break;
    case 1:
        aumenta_palheta(pal, *jog);
        jog->bonuspalheta = 1;
        break;
    case 2:
        aumenta_vida(jog);
    }
}

void printa_bonus(BOLA objetobonus)
//desenha bonus com caracter especial e cor azul
{
    textcolor(objetobonus.cor);
    gotoxy(objetobonus.posicao.x, objetobonus.posicao.y);
    printf("%c", SIMBOLO_BONUS);
}

int printa_winner()
//abre o arquivo com o texto "winner" e printa na tela
//retorna 0 se houve erro, retorna 1 se foi feito com sucesso
{
    FILE *arq;
    char linha[STRINGAO];

    if((arq = fopen("ganhou.txt", "r")) == NULL)
    {

        limpa_erro_arquivo();
        cputsxy(XINI + 1, YFIM + 1, "*** ERRO AO ABRIR O ARQUIVO GANHOU.TXT ***");
        return 0;
    }

    while(!feof(arq))
    {
        if(fgets(linha, sizeof(linha), arq) == NULL)
        {
            limpa_erro_arquivo();
            cputsxy(XINI + 1, YFIM + 1, "*** ERRO AO LER O ARQUIVO GANHOU.TXT ***");
            fclose(arq);
            return 0;
        }
        printf("%s", linha);
    }
    fclose(arq);
    return 1;
}

void animacao_winner()
//mostra o texto "winner" animado quando o jogador ganha o jogo
{
    char tecla = 0;
    textcolor(LIGHTGREEN);

    do
    {
        clrscr();
        Sleep(800);
        if(kbhit())
            tecla = getch();
        printa_winner();
        printf("\n\n\n\nPRESSIONE 'ENTER' PARA CONTINUAR\n");
        Sleep(1200);
        if(kbhit())
            tecla = getch();
    }
    while(tecla != ENTER);
}

void printa_score(JOGADOR score[])
//mostra numa tabela a pontuacao de todos os jogadores
{
    int i, jogador = 0;

    printf(" - PONTUACOES -\n\n");
    //printa a largura da tabela considerando o nome do jogador,
    //os cantos da tabela e o numero maximo de algarismos no tipo int
    for(i = 0; i < MAX_NOME_JOGADOR + 10; i++)
        printf("-");
    while(score[jogador].pontos != 0 && jogador < MAX_JOGADORES)
    //enquanto a pontuacao do jogador nao for nulo e nao chegou no maximo de jogadores
    {
        printf("\n|%*s |%6d |\n", MAX_NOME_JOGADOR - 1, score[jogador].nome, score[jogador].pontos);
        for(i = 0; i < MAX_NOME_JOGADOR + 10; i++)
            printf("-");
        jogador++;
    }
}

void animacao_troca_fase(COLORS cor)
//animacao para trocar de fase suavemente
{
    clrscr();
    textcolor(cor);
    gotoxy((XINI + XFIM)/2, (YINI + YFIM)/2);
    printf("CARREGANDO FASE");
    Sleep(250);
    gotoxy((XINI + XFIM)/2, (YINI + YFIM)/2);
    printf("CARREGANDO FASE.");
    Sleep(250);
    gotoxy((XINI + XFIM)/2, (YINI + YFIM)/2);
    printf("CARREGANDO FASE..");
    Sleep(250);
    gotoxy((XINI + XFIM)/2, (YINI + YFIM)/2);
    printf("CARREGANDO FASE...");
    Sleep(250);
    clrscr();
}

void pede_nome(JOGADOR *jog)
{
    gotoxy((XINI + XFIM)/2, (YINI + YFIM)/2);
    printf("Insira seu nome:");
    gotoxy((XINI + XFIM)/2, (YINI + YFIM)/2 + 2);
    gets(jog->nome);
}
