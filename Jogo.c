/* Nomes da dupla: Leo Hernandes de Vasconcelos e Nikolas Padao Schuster */

#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Estruturas_Constantes.h"
#include "arquivo.h"
#include "interface.h"
#include "movimento_colisao.h"
#include "menu.h"

//------------------------------------


short sem_tijolo(TIJOLO listatijolos[], int numeroTijolos)
//testa se no vetor de tijolos tem ainda algum que nao foi destruido,
//devolve 0 nesse caso, ou devolve 1 se foram todos destruidos
{
    int i;

    for(i = 0; i < numeroTijolos; i++)
    {
        if(listatijolos[i].status == 1) // se algum ainda existir
            return 0;                   // retorna 0
    }
    return 1; // se chegou ate o final, nao encontrou nenhum inteiro
}

void anula_tijolos(TIJOLO listaTijolos[])
//coloca o status de quebrado em todos os tijolos
//e zera suas coordenadas
{
    int tij;
    for(tij = 0; tij < NUMTIJ; tij++)
    {
        listaTijolos[tij].ponto1.x = 0;
        listaTijolos[tij].ponto1.y = 0;
        listaTijolos[tij].ponto2.x = 0;
        listaTijolos[tij].ponto2.y = 0;
        listaTijolos[tij].status = 2;
    }
}

void pausa(PAUSAJOGO *status, JOGADOR *jog, TIJOLO listaTijolos[], BOLA bol,PALHETA pal, char *tecla, FASE level[])
//pede o nome do jogador e salva todas as estruturas do jogo num arquivo binario com o nome do jogador
{
    int i;

    textcolor(WHITE);
    //apaga o nome antigo
    cputsxy(XSTATUS + 1,YINI + 4, "                          ");
    cputsxy(XSTATUS + 1,YINI + 1, "JOGO PAUSADO!");
    cputsxy(XSTATUS + 1,YINI + 2, "Insira o nome do usuario: ");

    fflush(stdin);
    gotoxy(XSTATUS + 1, YINI + 4);
    gets(jog->nome);
    cputsxy(XSTATUS + 1, YINI + 6, "aperte P para despausar");

    //apaga os caracteres a mais que botou no nome
    cputsxy(XSTATUS+1, YINI+2, "                         ");

    status->jog = *jog;
    status->bol = bol;
    status->pal = pal;
    for(i = 0; i < NUMTIJ; i++)
        status->listaTijolos[i] = listaTijolos[i];
    for(i = 0; i < ETAPAS; i++)
        status->level[i] = level[i];

    salva_estado_jogo(*status);
    do
    {
        *tecla = getch();
    }
    while(*tecla != ESC && *tecla != p && *tecla != P);
    //apaga a mensagem "aperte P para despausar"
    cputsxy(XSTATUS + 1, YINI + 6, "                         ");
    //apaga a mensagem de jogo pausado
    cputsxy(XSTATUS + 1, YINI + 1, "             ");
}

void instancia_jogo(PAUSAJOGO status, BOLA *bol, PALHETA *pal, TIJOLO listaTijolos[], JOGADOR *jog, FASE level[])
//le um arquivo binario com struct PAUSAJOGO e instancia
//em todas as variaveis do jogo os dados dessas estrutura
{
    int i;

    *bol = status.bol;
    *pal = status.pal;
    *jog = status.jog;
    for(i = 0; i < NUMTIJ; i++)
        listaTijolos[i] = status.listaTijolos[i];
    for(i = 0; i < ETAPAS; i++)
        level[i] = status.level[i];
}

int carrega_jogo(PAUSAJOGO *status)
//pede o nome do usuario pra encontrar o arquivo de save do jogo
//retorna 0 se houve erro, retorna 1 se foi feito com sucesso
{
    textcolor(WHITE);
    //apaga o nome antigo
    cputsxy(XSTATUS + 1,YINI + 4, "                          ");
    cputsxy(XSTATUS + 1,YINI + 1, "JOGO PAUSADO!");
    cputsxy(XSTATUS + 1,YINI + 2, "Insira o nome do usuario: ");

    fflush(stdin);
    gotoxy(XSTATUS + 1, YINI + 4);
    gets(status->jog.nome);
    cputsxy(XSTATUS+4, YINI+4, "                        ");
    cputsxy(XSTATUS + 1,YINI + 1, "             ");
    cputsxy(XSTATUS+1, YINI+2, "                         ");

    return(le_jogo_salvo(status));
}

int carrega_jogo_menu(PAUSAJOGO *status)
//pede o nome do usuario pra encontrar o arquivo de save do jogo no menu
//retorna 0 se houve erro, retorna 1 se foi feito com sucesso
{
    printf("Insira o mesmo nome que escolheu para salvar seu jogo:\n> ");
    gets(status->jog.nome);

    return(le_jogo_salvo(status));
}

void grava_pontuacao_endgame(JOGADOR jog, JOGADOR score[])
//quando o jogador perde ou ganha, salva sua pontuacao na lista
//de scores se for suficiente para entrar nos highscores
{
    clrscr();
    printf("Insira seu nome para salvarmos sua pontuacao final:\n> ");
    gets(jog.nome);

    clrscr();
    OrdenaListaJogadores(jog, score);
    SalvaListaJogadores(score);
    printa_score(score);
    printf("\n\nPressione qualquer tecla para voltar ao menu inicial...");
    getch();
}

int testa_fim_jogo(TIJOLO listatijolos[], JOGADOR *jog, JOGADOR score[])
//testa se o jogador perdeu todas as vidas ou destruiu todos os tijolos
//decide se muda de fase ou termina o jogo
{
    if(!jog->vidas) //se perder
    {
        animacao_game_over();
        grava_pontuacao_endgame(*jog, score);
        return 1;
    }
    else if(sem_tijolo(listatijolos, NUMTIJ)) //se ganhar
    {
        if(jog->fase == 2)
        {
            animacao_winner();
            grava_pontuacao_endgame(*jog, score);
            return 1;
        }
        else
            return 2;//troca de fase
    }

    return 0;
}

void troca_fase(JOGADOR *jog, JOGADOR score[], TIJOLO listatijolos[], FASE level[], PALHETA *pal, BOLA *bol)
//troca a fase, colocando o jogo no estado inicial,
//trocando layout de tijolos e algumas cores
{
    jog->fase += 1;
    if(jog->vidas < 3) //se tiver menos vidas, recarrega
        jog->vidas = 3;
    jog->bonusponto = 0;
    jog->bonuspalheta = 0;

    animacao_troca_fase(level[jog->fase].cor);

    pal->ponto1.x = POS_XINI_PALHETA;
    pal->ponto2.x = pal->ponto1.x + level[jog->fase].tam_pal - 1;

    //sons de troca de fase;
    Beep(1000,125);
    Beep(1500,125);

    printa_palheta(*pal);
    preenche_layout_tijolo(listatijolos, jog->fase);
    desenha_janela(level[jog->fase]);
    desenha_janela_informacoes(level[jog->fase]);
    printa_pontos(*jog);
    printa_vidas(*jog);
    OrdenaListaJogadores(*jog, score);
    MostraListaJogadores(*jog, score);

    //apaga a posicao da bolinha atual
    putchxy(bol->posicao.x,bol->posicao.y,' ');
    bol->velocidade_direcao.y = 0;                            //zera velocidade para entrar no estado inicial
    bol->posicao.x = ((pal->ponto1.x + pal->ponto2.x)/2) + 1; //coloca bolinha no meio da palheta
    bol->posicao.y = ALTURA_PALHETA - 1;                      //coloca bolinha na altura da palheta
    desenha_tijolos(listatijolos);                            //desenha os tijolos da proxima fase
    printa_bolinha(*bol);                                     //printa a bolinha na palheta
}

void menu(PAUSAJOGO *status, char *tecla, JOGADOR *jog, JOGADOR score[], BOLA *bol, PALHETA *pal, TIJOLO listaTijolos[], FASE level[])
// trata as teclas "P" para pausar o jogo e salva-lo e "C" para carregar um jogo
{
    switch(*tecla)
    {
    case p:
    case P:
        pausa(status, jog, listaTijolos, *bol, *pal, tecla, level);
        OrdenaListaJogadores(*jog, score);
        MostraListaJogadores(*jog, score);
        SalvaListaJogadores(score);
        break;
    case c:
    case C:
        if(!carrega_jogo(status)) //se nao deu erro
        {
            clrscr(); //limpa tudo para desenhar o jogo carregado
            instancia_jogo(*status, bol, pal, listaTijolos, jog, level);
            desenha_tijolos(listaTijolos);
            desenha_janela(level[jog->fase]);
            desenha_janela_informacoes(level[jog->fase]);
            printa_pontos(*jog);
            printa_vidas(*jog);
            printa_palheta(*pal);
            printa_bolinha(*bol);
            textcolor(WHITE);
            OrdenaListaJogadores(*jog, score);
            MostraListaJogadores(*jog, score);
        }
    }
}

void instancia_coord_bonus(TIJOLO tijolodestruido, BOLA *objetobonus)
//coloca as coordenados do tijolo destruido no objeto bonus
{
    objetobonus->posicao.x =(tijolodestruido.ponto2.x + tijolodestruido.ponto1.x)/2;
    objetobonus->posicao.y = tijolodestruido.ponto2.y + 1;
}

void gameloop(PALHETA pal, BOLA bol, TIJOLO listaTijolo[], FASE level[], JOGADOR jog, JOGADOR score[], PAUSAJOGO status)
//controla todas as teclas pressionadas e calcula as posicoes dos objetos na tela
{
    char tecla = 0;
    int temBonus, tijoloDestruido;
    int gameover = 0;
    int flagBonus = 1; //auxilia a nao deixar cair dois bonus ao mesmo tempo
    int loops = 0;     //contabiliza quantos loops foram feitos
    BOLA objetobonus = {{40, 10}, {0, 1}, LIGHTBLUE};

    textcolor(WHITE);
    esconde_cursor();
    while (tecla != ESC && !gameover)
    {
        gameover = testa_fim_jogo(listaTijolo, &jog, score);
        if(gameover == 2)
        {
            gameover = 0;
            troca_fase(&jog, score, listaTijolo, level, &pal, &bol);
        }

        if (kbhit())
        {
            tecla = getch();
            menu(&status, &tecla, &jog, score, &bol, &pal, listaTijolo, level);
            if (tecla == ESPECIAL || tecla == NUMPAD)
            {
                tecla = getch();
                move_palheta(tecla, &pal);
                if(!bol.velocidade_direcao.y)
                    //movimenta a bolinha junto com a palheta no inicio
                    bolinha_inicial(&bol, tecla, level[jog.fase]);
            }
            else if(tecla == BARRA_ESPACO && !bol.velocidade_direcao.y)
            //comeca o jogo quando pressiona espaco
            {
                bol.velocidade_direcao.y = -1;
            }
        }
        if(loops >= level[jog.fase].intervalo_bola && bol.velocidade_direcao.y != 0)
        {

            loops = 0; //reseta os loops
            move_bolinha(&bol, &pal, &jog, listaTijolo, &tijoloDestruido);
            if(tijoloDestruido >= 0) //se for um indice valido do tijolo que colidiu
            {
                temBonus = bonus();
                if(temBonus && flagBonus)
                {
                    //essa flag é pra dizer que pode mover o bonus na tela
                    flagBonus = 0;
                    //coloca as coordenados do tijolo destruido no objeto bonus
                    instancia_coord_bonus(listaTijolo[tijoloDestruido], &objetobonus);
                }

                destroi_tijolo(tijoloDestruido, listaTijolo, &jog, score, level); //destroi

            }
            //se a flag for 0 rodar a mover_bonus
            if(!flagBonus)
            //se o bonus atigir o fundo da moldura ou a palheta a flag vai virar 1, senao ficará 0
            {
                    flagBonus = move_bonus(listaTijolo, listaTijolo[tijoloDestruido], &objetobonus, &pal, &jog, level);
                    desenha_tijolos(listaTijolo);
            }
        }
        loops++; //conta os loops e deixa a bolinha se mexer dependendo do numero de loops
        Sleep(level[jog.fase].sleep);
    }
}

void seleciona_dificuldade(PALHETA pal, BOLA bol, TIJOLO listaTijolos[], FASE level[], JOGADOR jog, JOGADOR score[], PAUSAJOGO status)
//verifica qual dificuldade o jogador escolheu e muda as configuracoes do jogo de acordo
{
    int opcao = 1;
    clrscr();
    printa_dificuldades();
    move_seta_dificuldade(&opcao);

    switch(opcao)
    {
        case 1:
            level[0].intervalo_bola = 5;
            level[0].sleep = 27;
            level[0].tam_pal = 19;
            level[0].multiplicador = 1;
            level[1].intervalo_bola = 5;
            level[1].sleep = 27;
            level[1].tam_pal = 19;
            level[1].multiplicador = 1;
            level[2].intervalo_bola = 5;
            level[2].sleep = 27;
            level[2].tam_pal = 19;
            level[2].multiplicador = 1;
            break;
        case 2:
            level[0].intervalo_bola = 5;
            level[0].sleep = 20;
            level[0].tam_pal = 19;
            level[0].multiplicador = 1;
            level[1].intervalo_bola = 4;
            level[1].sleep = 22;
            level[1].tam_pal = 17;
            level[1].multiplicador = 2;
            level[2].intervalo_bola = 4;
            level[2].sleep = 22;
            level[2].tam_pal = 15;
            level[2].multiplicador = 4;
            break;
        case 3:
            level[0].intervalo_bola = 4;
            level[0].sleep = 15;
            level[0].tam_pal = 17;
            level[0].multiplicador = 2;
            level[1].intervalo_bola = 4;
            level[1].sleep = 15;
            level[1].tam_pal = 15;
            level[1].multiplicador = 4;
            level[2].intervalo_bola = 4;
            level[2].sleep = 15;
            level[2].tam_pal = 13;
            level[2].multiplicador = 8;
    }
    clrscr();
    pede_nome(&jog);
    //zera tijolos para carregar os novos quando iniciar novo jogo
    anula_tijolos(listaTijolos);
    gameloop(pal, bol, listaTijolos, level, jog, score, status);
}

int seleciona_menu(PALHETA pal, BOLA bol, TIJOLO listaTijolos[], FASE level[], JOGADOR jog, JOGADOR score[], PAUSAJOGO status)
//printa as setas nas opcoes, permitindo o usuario escolher
//retorna 0 quando o usuario quer sair, retorna 1 quando o usuario escolher outra opcao
{
    int opcao = 1;

    move_seta(&opcao);
    Beep(500, 300);
    //verifica qual opcao ele quis
    clrscr();
    switch(opcao)
    {
        case 1:
            seleciona_dificuldade(pal, bol, listaTijolos, level, jog, score, status);
            break;
        case 2:
            if(!carrega_jogo_menu(&status)) //se nao deu erro
            {
                clrscr(); //limpa tudo para desenhar o jogo carregado
                instancia_jogo(status, &bol, &pal, listaTijolos, &jog, level);
                desenha_tijolos(listaTijolos);
                desenha_janela(level[jog.fase]);
                desenha_janela_informacoes(level[jog.fase]);
                printa_pontos(jog);
                printa_vidas(jog);
                printa_palheta(pal);
                printa_bolinha(bol);
                textcolor(WHITE);
                OrdenaListaJogadores(jog, score);
                MostraListaJogadores(jog, score);
                //inicia jogo
                gameloop(pal, bol, listaTijolos, level, jog, score, status);
            }
            else
            {
                clrscr();
                textcolor(RED);
                printf("\n** NAO ENCONTRAMOS ESSE JOGO SALVO **");
                printf("\n\n\n Pressione qualquer tecla para retornar");
                getch();
            }
            break;
        case 3:
            printa_score(score);
            getch();
            break;
        case 4:
            printa_instrucoes();
            getch();
            break;
        case 5:
            printa_creditos();
            getch();
            break;
        case 6:
            //se o usuario escolheu sair, retorna 0
            return 0;
    }

    //se o usuario nao quis sair, devolve 1 para
    //sinalizar para funcao externa
    return 1;
}

void controla_menu(PALHETA pal, BOLA bol, TIJOLO listaTijolos[], FASE level[], JOGADOR jog, JOGADOR score[], PAUSAJOGO status)
//mantem o usuario no menu ate que ele deseje sair
{
    do
    {
        printa_main_menu();
    }while(seleciona_menu(pal, bol, listaTijolos, level, jog, score, status));
}

int main()
{
    PALHETA pal = {{POS_XINI_PALHETA, ALTURA_PALHETA}, {POS_XINI_PALHETA, ALTURA_PALHETA}, MAGENTA};
    BOLA bol = {{0, ALTURA_PALHETA - 1}, {1, 0}, GREEN};
    TIJOLO listaTijolo[NUMTIJ] = {};
    FASE level[ETAPAS] =
    {
        {0, 0, DARKGRAY, 1, 0},
        {0, 0, CYAN, 2, 0},
        {0, 0, BROWN, 4, 0}
    };
    JOGADOR jog = {"", VIDAS, -1, 0, 0, 0};
    JOGADOR score[MAX_JOGADORES] = {};
    PAUSAJOGO status = {jog};
    FILE *arqtxt;

    if(AbreArqJog(&arqtxt))
        //ja carrega a lista de scores
        LeArqTexto(arqtxt, score);

    srand(time(0)); //coloca a seed no clock do sistema
    esconde_cursor();

    controla_menu(pal, bol, listaTijolo, level, jog, score, status);

    clrscr();
    gotoxy(1, 1);
    textcolor(WHITE);

    return 0;
}
