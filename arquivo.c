#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Estruturas_Constantes.h"
#include "interface.h"

int salva_estado_jogo(PAUSAJOGO status)
// salva todas as estruturas do jogo num arquivo binario
{
    FILE *save;
    char nomeArquivo[MAX_NOME_JOGADOR + 4]; // +4 para concatenar ".bin"
    strcpy(nomeArquivo, status.jog.nome);   // copia o nome do jogador
    strcat(nomeArquivo, ".bin");            // coloca ".bin" no final
    if((save = fopen(nomeArquivo, "wb")) == NULL)
    {
        limpa_erro_arquivo();
        cputsxy(XINI, YFIM + 1, "\n*** ERRO AO CRIAR ARQUIVO PARA SALVAR PROGRESSO ***\n");
        return 1;
    }

    if(fwrite(&status, sizeof(PAUSAJOGO), 1, save) != 1)
    {
        limpa_erro_arquivo();
        cputsxy(XINI, YFIM + 1, "\n*** ERRO AO TENTAR SALVAR O PROGRESSO ***\n");
        fclose(save);
        return 1;
    }
    fclose(save);
    return 0;
}

int le_jogo_salvo(PAUSAJOGO *status)
// le jogo salvo de um arquivo com o nome do jogador
{
    FILE *save;
    char nomeArquivo[MAX_NOME_JOGADOR + 4]; // +4 para concatenar ".bin"
    strcpy(nomeArquivo, status->jog.nome);  // copia o nome do jogador
    strcat(nomeArquivo, ".bin");            // coloca ".bin" no final

    if((save = fopen(nomeArquivo, "rb")) == NULL)
    {
        limpa_erro_arquivo();
        cputsxy(XINI, YFIM + 1, "\n*** ERRO AO ABRIR O ARQUIVO DE JOGO SALVO ***\n");
        return 1;
    }

    if(fread(status, sizeof(PAUSAJOGO), 1, save) != 1)
    {
        limpa_erro_arquivo();
        cputsxy(XINI, YFIM + 1, "\n*** ERRO AO CARREGAR AQUIVRO DE JOGO SALVO ***\n");
        fclose(save);
        return 1;
    }
    fclose(save);
    return 0;
}

int carrega_tijolos(TIJOLO listaTijolos[], FILE *arq)
//preenche o vetor de tijolos com o arquivo dado
//devolve zero se houver erro e um se for feito com sucesso
{
    TIJOLO buffer;
    int i = 0;

    while(!feof(arq))
    {
        if(fread(&buffer, sizeof(TIJOLO), 1, arq) != 1 && !feof(arq))
        {
            limpa_erro_arquivo();
            cputsxy(XINI + 1, YFIM + 1, "\n*** ERRO AO LER O ARQUIVO COM LAYOUT***\n");
            fclose(arq);
            return 0;
        }
        else if(!feof(arq))
        //por causa do teste !feof(arq) acima, ele preenche duas vezes com o ultimo termo
        //precisa desse teste pra evitar isso
        {
            listaTijolos[i] = buffer;
            i++;
        }
    }
    fclose(arq);
    return 1;
}

int preenche_layout_tijolo(TIJOLO listaTijolos[], int fase)
// abre o arquivo do layout de tijolos da fase dada e preenche o vetor de tijolos,
// devolve zero se houve erro e nao zero se deu tudo certo
{
    FILE *arq;
    char numFase = fase + '1'; //converte inv para char
    char nomeFase[19] = {"level_layout_x.bin"};

    nomeFase[13] = numFase;

    if((arq = fopen(nomeFase, "rb")) == NULL)
    {
        limpa_erro_arquivo();
        cputsxy(XINI + 1, YFIM + 1, "***ERRO AO ABRIR O ARQUIVO COM LAYOUT***");
        return 0;
    }

    return(carrega_tijolos(listaTijolos, arq));
}

int AbreArqJog(FILE **arqtxt)
//abre o arquivo de pontuacao, devolve zero se houve erro e nao zero se deu certo
{

    if((*arqtxt = fopen("BreakoutJog.txt", "r")) == NULL)
    {
        limpa_erro_arquivo();
        cputsxy(XINI + 1, YFIM + 1, "***ERRO AO ABRIR O ARQUIVO COM SCORES***");
        return 0;
    }
    else
        return 1;
}
void preenche_jogador_pnts(FILE *arqtxt, JOGADOR *jog)
// pega uma linha do arquivo de pontuacao e preenche um jogador
{
    char linhaPontuacao[MAX_NOME_JOGADOR + 10];
    char *token;

    //le uma linha inteira do arquivo texto
    fgets(linhaPontuacao, sizeof(linhaPontuacao), arqtxt);
    //le ate o sustenido e pega o nomes
    token = strtok(linhaPontuacao, "#");
    //passa para a estrutura
    strcpy(jog->nome, token);
    //pega o numero
    token = strtok(NULL, "#");
    //transforma a string em numero
    jog->pontos = atoi(token);

}


int LeArqTexto(FILE *arqtxt, JOGADOR score[])
//preenche todo um vetor de jogadores com os dados do arquivo dado
{
    int jogador = 0;

    while(!feof(arqtxt) && jogador < 5)
    {
        preenche_jogador_pnts(arqtxt, &score[jogador]);
        jogador++;
    }
    fclose(arqtxt);
    //retorna quantos jogadores preencheu
    return jogador;
}

int SalvaListaJogadores (JOGADOR lista[])
/* Sobrescreva o arquivo texto BreakoutJog.txt com os cinco nomes de jogadores que tiveram
as maiores pontuações, mantendo o formato original do arquivo. Ou seja, as pontuações são
demarcadas por #.  Retorne 1 se a operação foi realizada com sucesso e zero se o arquivo não
pode ser salvo. Se não existiam 5 nomes no arquivo original devem ser salvos os jogadores
anteriores  e o atual, sem repetição de nomes.  */
{
    int i = 0;
    FILE *arqtxt;

    if((arqtxt = fopen("BreakoutJog.txt", "w")) == NULL)
    {
        limpa_erro_arquivo();
        cputsxy(XINI + 1, YFIM + 1, "*** ERRO AO ABRIR O ARQUIVO PARA SALVAR AS PONTUACOES ***");
        return 0;
    }
    else
    {
        while(i < 5 && lista[i].pontos != 0)
        //se o jogador não tiver pontuacao, para a gravacao pois o vetor está ordenado
        {

            if(fprintf(arqtxt,"%s#%d\n",lista[i].nome,lista[i].pontos) < 0)
            {
                limpa_erro_arquivo();
                cputsxy(XINI + 1, YFIM + 1, "*** ERRO AO GRAVAR AS PONTUACOES ***");
                fclose(arqtxt);
                return 0;//não escreveu com êxito
            }
            i++;
        }
        fclose(arqtxt);
        return 1;//escreveu certo
    }
}
