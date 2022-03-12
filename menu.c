#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include "Estruturas_Constantes.h"
#include "interface.h"

void printa_moldura_main_menu()
//printa a moldura que engloba o titulo do jogo
{
    int i;

    textcolor(MAGENTA);
    gotoxy(TITULO_XINI, TITULO_YINI);
    printf("%c", BORDA_SE);    //canto superior esquerdo
    for(i = TITULO_XINI + 1; i < TITULO_XFIM; i++)
    {
        printf("%c", BARRA_H);   //borda superior
    }
    printf("%c", BORDA_SD);    //canto superior direito
    for(i = TITULO_YINI + 1; i < TITULO_YFIM; i++)
    {
        gotoxy(TITULO_XFIM, i);
        printf("%c", BARRA_V);   //borda direita
    }

    gotoxy(TITULO_XINI, TITULO_YINI + 1);
    for(i = TITULO_YINI + 1; i < TITULO_YFIM; i++)
    {
        gotoxy(TITULO_XINI, i);
        printf("%c", BARRA_V); //borda esquerda
    }
    gotoxy(TITULO_XINI, TITULO_YFIM);
    printf("%c", BORDA_IE);      //canto inferior esquerdo
    for(i = TITULO_XINI + 1; i < TITULO_XFIM; i++)
    {
        printf("%c", BARRA_H);   //borda inferior
    }
    printf("%c", BORDA_ID);      //canto inferior direito
}

void printa_help_main_menu()
{
    gotoxy(TITULO_XINI - 10, TITULO_YFIM + 18);
    textcolor(WHITE);
    printf("Pressione as setas para ");
    textcolor(BROWN);
    printf("CIMA ");
    textcolor(WHITE);
    printf("e para ");
    textcolor(BROWN);
    printf("BAIXO ");
    textcolor(WHITE);
    printf("para navegar no menu");
    gotoxy(TITULO_XINI - 10, TITULO_YFIM + 20);
    printf("Pressione ");
    textcolor(BROWN);
    printf("ENTER ");
    textcolor(WHITE);
    printf("para escolher a opcao");
}

int printa_main_menu()
//carrega o arquivo que tem a ilustracao do main menu e printa na tela
//retorna zero se houve erro, retorna 1 se foi feito com sucesso
{
    FILE *arq;
    char linha[STRINGAO];

    clrscr(); //limpa a tela de qualquer funcao que estava executando antes
    if((arq = fopen("main_menu.txt", "r")) == NULL)
    {
        limpa_erro_arquivo();
        cputsxy(XINI, YFIM + 1, "*** ERRO AO ABRIR O ARQUIVO DO MAIN_MENU ***");
        return 0;
    }

    textcolor(LIGHTMAGENTA);
    while(!feof(arq))
    {
        if(fgets(linha, sizeof(linha), arq) == NULL)
        {
            limpa_erro_arquivo();
            cputsxy(XINI, YFIM + 1, "*** ERRO AO LER ARQUIVO DO MAIN_MENU ***");
            fclose(arq);
            return 0;
        }
        else
            printf("%s", linha);
    }
    fclose(arq);
    printa_moldura_main_menu();
    printa_help_main_menu();
    return 1;
}

int printa_creditos()
//abre o arquivo dos creditos e printa na tela
//retorna 0 se houve erro, devolve 1 se foi feito com sucesso
{
    FILE *arq;
    char linha[STRINGAO];

    if((arq = fopen("creditos.txt", "r")) == NULL)
    {
        limpa_erro_arquivo();
        cputsxy(XINI, YFIM + 1, "*** ERRO AO ABRIR OS CREDITOS ***");
        return 0;
    }

    textcolor(LIGHTGREEN);
    while(!feof(arq))
    {
        if(fgets(linha, sizeof(linha), arq) == NULL)
        {
            limpa_erro_arquivo();
            cputsxy(XINI, YFIM + 1, "*** ERRO AO ABRIR OS CREDITOS ***");
            fclose(arq);
            return 0;
        }
        printf("%s", linha);
    }
    fclose(arq);
    return 1;
}

void printa_limpa_seta(int opcao, short acao)
//dependendo do numero da opcao, printa uma seta na opcao no menu
//se a acao for o numero 1, mas limpa a seta se a acao for o numero 2
{
    //vai para a posicao correta de acordo com a opcao
    gotoxy(SETA_X, TITULO_YFIM + (opcao * 2));

    if(acao == 1)
    {
        textcolor(LIGHTRED);
        printf(">>");
        //coloca a seta
    }
    else if(acao == 2)
        printf("  ");
        //apaga a seta
}

void gera_opcao(char tecla, int *opcao)
//verifica qual a proxima posicao da seta de
//acordo com o input do usuario
{
    switch(tecla)
    {
        case SETA_CIMA:
            //se a seta estiver na opcao 1, volta para baixo
            if(*opcao == 1)
                *opcao = 6;
            else
                (*opcao)--;
            break;
        case SETA_BAIXO:
            //se a seta estiver na opcao 4, volta pra cima
            if(*opcao == 6)
                *opcao = 1;
            else
                (*opcao)++;
    }
}

void move_seta(int *opcao)
//move a seta ate que o usuario pressione enter
//devolve por referencia a opcao que o usuario escolheu
{
    char tecla;

    while(tecla != ENTER)
    {
        printa_limpa_seta(*opcao, 1);

        tecla = getch();
        if(tecla == NUMPAD || tecla == ESPECIAL)
        {
            tecla = getch();
            printa_limpa_seta(*opcao, 2);
            gera_opcao(tecla, opcao);
        }
    }
    //quando sair do loop, usuario apertou enter
}

void printa_instrucoes()
//mostra instrucoes para iniciar o jogo
{
    textcolor(LIGHTRED);
    printf("\n\n               PARA UMA MELHOR EXPERIENCIA:                \n\n\n\n");
    textcolor(WHITE);
    printf(" Pressione o ");
    textcolor(BROWN);
    printf("BOTAO DIREITO");
    textcolor(WHITE);
    printf(" do mouse na aba do console e clique em\n\n");
    textcolor(LIGHTGREEN);
    printf("  propriedades -> fontes -> fontes de varredura");
    textcolor(WHITE);
    printf(" e clique em ");
    textcolor(LIGHTGREEN);
    printf("OK.\n\n");
    textcolor(WHITE);
    printf(" Logo apos, pressione ");
    textcolor(BROWN);
    printf("ALT + ENTER");
    textcolor(WHITE);
    printf(" no menu para entrar em tela cheia!\n\n\n\n");
    textcolor(LIGHTRED);
    printf("                 BOA SORTE E DIVIRTA-SE!                ");
}

void printa_dificuldades()
//mostra no menu as dificuldades para o usuario escolher
{
    gotoxy(31, 11);
    textcolor(MAGENTA);
    printf("ESCOLHA UMA DIFICULDADE");
    gotoxy(40, 17);
    textcolor(YELLOW);
    printf("Facil");
    gotoxy(40, 19);
    textcolor(LIGHTRED);
    printf("Medio");
    gotoxy(39, 21);
    textcolor(RED);
    printf("Dificil");
}

void gera_opcao_dificuldade(char tecla, int *opcao)
//verifica qual a proxima posicao da seta de
//acordo com o input do usuario
{
    switch(tecla)
    {
        case SETA_CIMA:
            //se a seta estiver na opcao 1, volta para baixo
            if(*opcao == 1)
                *opcao = 3;
            else
                (*opcao)--;
            break;
        case SETA_BAIXO:
            //se a seta estiver na opcao 4, volta pra cima
            if(*opcao == 3)
                *opcao = 1;
            else
                (*opcao)++;
    }
}

void move_seta_dificuldade(int *opcao)
//move a seta ate que o usuario pressione enter
//devolve por referencia a dificuldade que o usuario escolheu
{
    char tecla;

    while(tecla != ENTER)
    {
        printa_limpa_seta(*opcao, 1);

        tecla = getch();
        if(tecla == NUMPAD || tecla == ESPECIAL)
        {
            tecla = getch();
            printa_limpa_seta(*opcao, 2);
            gera_opcao_dificuldade(tecla, opcao);
        }
    }
    //quando sair do loop, usuario apertou enter
}
