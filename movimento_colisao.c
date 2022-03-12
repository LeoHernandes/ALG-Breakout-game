#include <conio2.h>
#include <windows.h>
#include "Estruturas_Constantes.h"
#include "interface.h"

short testa_colisao(int x1Obj1, int x2Obj1, int y1Obj1, int y2Obj1, int x1Obj2, int x2Obj2, int y1Obj2, int y2Obj2)
//verifica pelo metodo de envelope se um objeto1 esta' dentro de outro objeto2
{
    if(x1Obj2 <= x2Obj1 && x2Obj2 >= x1Obj1 && y1Obj2 <= y2Obj1 && y2Obj2 >= y1Obj1)
        return 1;

    return 0; //se nao colidiu, retorna 0
}

void move_palheta(char tecla, PALHETA *pal)
//se for possivel, movimenta a palheta para direita ou esquerda
{
    switch(tecla)
    {
    case SETA_DIREITA:
        if(pal->ponto2.x + 1 < XFIM)
        {
            putchxy(pal->ponto1.x, pal->ponto1.y, ' '); //apaga o lado esquerdo
            pal->ponto1.x++;                  //atualiza a posicao da palheta
            pal->ponto2.x++;
            printa_palheta(*pal);
        }
        break;
    case SETA_ESQUERDA:
        if(pal->ponto1.x - 1 > XINI)
        {
            if(pal->ponto2.x < XFIM)
            //quando a palheta aumenta pra direita com o bonus, fica fora
            //da moldura ate retirar ela de lá, logo nao podemos apagar
            //o lado direito dela para nao apagar informacoes fora da moldura
            {
                putchxy(pal->ponto2.x, pal->ponto2.y, ' '); //apaga o lado direito
            }
            pal->ponto1.x--;
            pal->ponto2.x--;
            printa_palheta(*pal);
        }
        break;
    }
}

void bolinha_inicial(BOLA *bol, char tecla, FASE fase)
//movimenta a bolinha junto com a palheta no inicio do jogo
//ate pressionar espaco e jogar ela pra cima
{
    int metade_pal = (fase.tam_pal/2);

    switch(tecla)
    {
    case SETA_DIREITA:
        if(bol->posicao.x + metade_pal + 1 < XFIM)
        {
            putchxy(bol->posicao.x, bol->posicao.y, ' ');
            bol->posicao.x += 1;
            bol->velocidade_direcao.x = 1;
            printa_bolinha(*bol);
        }
        break;
    case SETA_ESQUERDA:
        if(bol->posicao.x - metade_pal - 1 > XINI)
        {
            putchxy(bol->posicao.x, bol->posicao.y, ' ');
            bol->posicao.x -= 1;
            bol->velocidade_direcao.x = -1;
            printa_bolinha(*bol);
        }
    }
}

void colisao_bolinha_palheta(BOLA *bol, PALHETA pal)
//redireciona a bolinha de acordo com a posicao onde ela colidiu com a palheta
{
    int metadePal = ((pal.ponto2.x + pal.ponto1.x)/2);

    //inverte a direcao vertical
    bol->velocidade_direcao.y *= -1;

    if(bol->velocidade_direcao.x > 0 && bol->posicao.x <= metadePal && bol->posicao.x - 1 != XINI)
        //se estava indo pra direita e bateu na metade esquerda da palheta
        //e nao esta colado na moldura, inverte a direcao horizontal
        bol->velocidade_direcao.x *= -1;
    else if(bol->velocidade_direcao.x < 0 && bol->posicao.x > metadePal && bol->posicao.x + 1 != XFIM)
        //se estava indo pra esquerda e bateu na metade direita da palheta
        //e nao esta colado na moldura, inverte a direcao horizontal
        bol->velocidade_direcao.x *= -1;
}

void perde_vida_bolinha(BOLA *bol, JOGADOR *jog, PALHETA *pal, TIJOLO listaTijolos[])
//tira vidas e coloca a bolinha no estado inicial, parada em cima da palheta
{
    int metadePal;
    if(jog->bonuspalheta == 1)
    {
        jog->bonuspalheta = 0;
        tira_bonus_palheta(pal);                 //tira o bonus da palheta
    }

    //calcula a metade da palheta depois de possivelmente perder o bonus
    metadePal = ((pal->ponto1.x + pal->ponto2.x)/2) + 1;

    if(jog->bonusponto == 1)
    {
        jog->bonusponto = 0;
        tira_bonus_pontos(listaTijolos);          //tira o bonus de pontos
    }

    jog->vidas--;                                 //tira uma vida
    printa_vidas(*jog);                           //printa as vidas novamente
    putchxy(bol->posicao.x, bol->posicao.y, ' '); //apaga a bolinha
    bol->velocidade_direcao.y = 0;                //zera velocidade para entrar no estado inicial
    bol->posicao.x = metadePal;                   //coloca bolinha no meio da palheta
    bol->posicao.y = ALTURA_PALHETA - 1;          //coloca bolinha na altura da palheta
}

void colisao_bolinha_moldura(BOLA *bol, JOGADOR *jog, PALHETA *pal, TIJOLO listaTijolos[])
//redireciona a bollinha se ela bater na moldura
{
    int bolaProx_x = bol->posicao.x + bol->velocidade_direcao.x;
    int bolaProx_y = bol->posicao.y + bol->velocidade_direcao.y;
    if(bolaProx_x == XINI || bolaProx_x == XFIM) //se tiver colado na borda direita ou esquerda
        bol->velocidade_direcao.x *= -1;
    if(bolaProx_y == YINI)       //se tiver colado na borda superior
        bol->velocidade_direcao.y *= -1;
    else if (bolaProx_y == YFIM) //se tiver colado na borda inferior
    {
        Beep(100,250);
        perde_vida_bolinha(bol, jog, pal, listaTijolos);
    }

}

void colisao_bolinha_tijolo(TIJOLO tij, BOLA *bol)
//redireciona a bolinha de acordo com a colisao no tijolo
{
    if((bol->posicao.x > tij.ponto2.x) || (bol->posicao.x < tij.ponto1.x)) //se bateu nas laterais
        bol->velocidade_direcao.x *= -1;
    else //se bateu em cima ou embaixo
        bol->velocidade_direcao.y *= -1;
}

int testa_colisao_bolinha_tijolo(TIJOLO listatijolos[], BOLA *bol)
//testa colisao da bolinha com tijolo e possivelmente muda sua direcao, retorna com qual tijolo bateu
{
    int i = 0;
    int xbolProx = bol->posicao.x + bol->velocidade_direcao.x;
    int ybolProx = bol->posicao.y + bol->velocidade_direcao.y;

    do
    {
        if(testa_colisao(xbolProx, xbolProx, ybolProx, ybolProx, listatijolos[i].ponto1.x, listatijolos[i].ponto2.x, listatijolos[i].ponto1.y, listatijolos[i].ponto2.y))
        {
            colisao_bolinha_tijolo(listatijolos[i], bol); //modifica a direcao da bolinha
            return i;
        }
        i++;
    }
    while(i < NUMTIJ);  //enquanto nao encontrou com qual tijolo bateu ou n testou todos os tijolos

    return -1;
}

void move_bolinha(BOLA *bol, PALHETA *pal, JOGADOR *jog, TIJOLO listaTijolos[], int *indiceTij)
//printa a proxima posicao da bolinha, considerando colisoes na moldura e palheta e nos tijolos
{
    int xbolProx;
    int ybolProx;


    //testa a colisao com a bola na sua proxima posicao, para saber se ela pode se mexer ou nao
    colisao_bolinha_moldura(bol, jog, pal, listaTijolos);

    //atualiza novamente a posicao da bolinha para caso ela tenha
    //uma direcao diferente apos colidir com a moldura
    xbolProx = bol->posicao.x + bol->velocidade_direcao.x;
    ybolProx = bol->posicao.y + bol->velocidade_direcao.y;

    if(testa_colisao(xbolProx, xbolProx, ybolProx, ybolProx, pal->ponto1.x, pal->ponto2.x, pal->ponto1.y, pal->ponto2.y))
    {
        colisao_bolinha_palheta(bol, *pal);
    }

    *indiceTij = testa_colisao_bolinha_tijolo(listaTijolos, bol);

    putchxy(bol->posicao.x, bol->posicao.y, ' '); //apaga a bolinha anterior
    bol->posicao.x += bol->velocidade_direcao.x;
    bol->posicao.y += bol->velocidade_direcao.y; //atualiza a posicao da bola
    printa_bolinha(*bol);
}


int move_bonus(TIJOLO listatijolo[], TIJOLO tijolodestruido,BOLA *objetobonus, PALHETA *pal, JOGADOR *jog, FASE level[])
//move o caracter do bonus pela tela, considerando colisao na palheta e na parte inferior da moldura
{
    int ybonusProx;
    //proximo y do objeto bonus
    ybonusProx = objetobonus->posicao.y + objetobonus->velocidade_direcao.y;

    //se colidir com a palheta
    if(testa_colisao(objetobonus->posicao.x, objetobonus->posicao.x, ybonusProx, ybonusProx, pal->ponto1.x, pal->ponto2.x, pal->ponto1.y, pal->ponto2.y))
    {
        //dar o bonus pro jogador
        gera_bonus(listatijolo, pal, jog, level[jog->fase]);//jogador pegou bonus com a palheta
        //dar um beep pra confirmar que pegou
        Beep(3500,250);
        putchxy(objetobonus->posicao.x, objetobonus->posicao.y, ' ');//apaga o objeto bonus atual
        return 1;// parar de mover o bonus
    }
    //se colidir com o fundo da moldura
    if(ybonusProx == YFIM)
    {
        putchxy(objetobonus->posicao.x, objetobonus->posicao.y, ' ');//apaga o objeto bonus atual
        return 1;// parar de mover o bonus
    }

    putchxy(objetobonus->posicao.x, objetobonus->posicao.y, ' '); //apaga o objeto bonus anterior
    objetobonus->posicao.y += objetobonus->velocidade_direcao.y; //atualiza a posicao do objeto bonus
    printa_bonus(*objetobonus);//printa o bonus de acordo com a posicao x,y dele
    return 0;//nao parar de mover o bonus
}
