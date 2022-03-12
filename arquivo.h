int salva_estado_jogo(PAUSAJOGO status);

int le_jogo_salvo(PAUSAJOGO *status);

int carrega_tijolos(TIJOLO listaTijolos[], FILE *arq);

int preenche_layout_tijolo(TIJOLO listaTijolos[], int fase);

int AbreArqJog(FILE **arqtxt);

void preenche_jogador_pnts(FILE *arqtxt, JOGADOR *jog);

int LeArqTexto(FILE *arqtxt, JOGADOR score[]);

int SalvaListaJogadores (JOGADOR lista[]);
