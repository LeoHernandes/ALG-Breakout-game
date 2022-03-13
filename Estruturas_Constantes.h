#include <conio2.h>
//-------- CONSTANTES FISICAS --------
typedef enum
{
    POS_XINI_PALHETA = 25,
    ALTURA_PALHETA = 31,
    XINI = 1,
    XFIM = 70,
    YINI = 2,
    YFIM = 35,
    XINFO = 1,
    YINFO = 1,
    XSTATUS = 72,
    YSTATUS = 3,
    XPONTOS = 72,
    YPONTOS = 24,
    TITULO_XINI = 16,
    TITULO_XFIM = 70,
    TITULO_YINI = 9,
    TITULO_YFIM = 15,
    SETA_X = 32,
    JANELAINFO_LARGURA = 35,
    ALTURA_DIVISAO = 15,
    ALTURA_DIVISAO2 = 10
} FISICA;
//-------- CONSTANTES ASCII --------
typedef enum
{
    SIMBOLO_TIJOLO = 177,
    BARRA_V = 186,
    BORDA_SD = 187,
    BORDA_ID = 188,
    BORDA_IE = 200,
    BORDA_SE = 201,
    BARRA_H = 205,
    SIMBOLO_PALHETA = 223,
    SIMBOLO_BOLINHA = 254,
    ESPECIAL = -32, //caractere especial
    NUMPAD = 0, //valor do primeiro getch do teclado numérico
    SETA_DIREITA = 77,
    SETA_ESQUERDA = 75,
    SETA_CIMA = 72,
    SETA_BAIXO = 80,
    BARRA_ESPACO = 32,
    ENTER = 13,
    ESC = 27,
    p = 112,
    P = 80,
    c = 99,
    C = 67,
    CORACAO = 3,
    SIMBOLO_BONUS = 207
} ASCII;

//-------- CONFIG ---------
typedef enum
{
    ETAPAS = 3,
    VIDAS = 3,
    NUMTIJ = 66,
    MAX_NOME_JOGADOR = 25,
    MAX_JOGADORES = 5,
    STRINGAO = 256,
    PROB_BONUS = 5
} CONFIG_JOGO;

//------ ESTRUTURAS --------
typedef struct
//ESTRUTURA COORDENADA
{
    int x;
    int y;
} COORDENADA;

typedef struct
//ESTRUTURA BOLA
{
    COORDENADA posicao;            // posicao da bola no jogo
    COORDENADA velocidade_direcao; // direcao e velocidade de deslocamento
    COLORS cor;                    // cor da bola
} BOLA;

typedef struct
//ESTRUTURA PALHETA
{
    COORDENADA ponto1;              // coordenada do canto superior esq do envelope
    COORDENADA ponto2;              // coordenada do canto inferior dir do envelope
    COLORS cor;                     // cor da palheta
} PALHETA;

typedef struct
//ESTRUTURA JOGADOR
{
    char nome[MAX_NOME_JOGADOR]; // nome com 3 letras
    int vidas;    // quantidade de vidas restantes
    int fase;     // fase em que esta' jogando
    int pontos;   // pontuacao atual
    short bonusponto; //é 1 se ele está com o buff de pontos, é 0 se não está
    short bonuspalheta; //é 1 se ele está com o buff da palheta, é 0 se não está
} JOGADOR;

typedef struct
//ESTRUTURA TIJOLO
{
    COORDENADA ponto1; // coordenada do canto superior esq do envelope
    COORDENADA ponto2; // coordenada do canto inferior dir do envelope
    short status;      // estado do tijolo (1 para inteiro e 2 para quebrado)
    int pontos;        // pontos que gera quando quebrado
    int bonus;         // quantidade de pontos a mais que o tijolo gera quando quebrado
    short vidas;       // quantidade de colisoes que precisam para destruir o tijolo
} TIJOLO;

typedef struct
//ESTRUTURA FASE
{
    int intervalo_bola; // intervalo em que a bola se movimenta, quando maior, mais devagar ela mexe
    int sleep;         // velocidade do jogo inteiro, quanto maior o sleep, mais devagar o jogo
    COLORS cor;        // cor da moldura da fase, pra diferenciar as fases
    int multiplicador; //fase 1 os tijolos tem 1x pontos, fase 2 tijolos tem 2x pontos, fase 3 tijolos tem 4x pontos
    int tam_pal;      // tamanho da palheta em certa fase
} FASE;

typedef struct
//ESTRUTURA PAUSA JOGO
{
    JOGADOR jog;
    TIJOLO listaTijolos[NUMTIJ];
    BOLA bol;
    PALHETA pal;
    FASE level[ETAPAS];
}PAUSAJOGO;
