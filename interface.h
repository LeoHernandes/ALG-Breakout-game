void esconde_cursor();

void desenha_janela();

void desenha_janela_informacoes();

void printa_palheta(PALHETA pal);

void printa_bolinha(BOLA bol);

void desenha_tijolo(TIJOLO *tij);

void escolhe_cor_tijolo(TIJOLO tij);

void desenha_tijolos(TIJOLO listatijolo[]);

void printa_pontos(JOGADOR jog);

void printa_vidas(JOGADOR jog);

void apaga_tijolo(TIJOLO tij);

void destroi_tijolo(int indicetijolo, TIJOLO listatijolo[], JOGADOR *jog, JOGADOR score[], FASE level[]);

void limpa_erro_arquivo();

void animacao_game_over();

int bonus();

void info_bonus(char *bonus);

void limpa_bonus();

void gera_bonus();

void limpa_palheta(PALHETA pal);

void aumenta_pontos(TIJOLO listaTijolos[]);

void aumenta_palheta(PALHETA *pal, JOGADOR jog);

void aumenta_vida(JOGADOR *jog);

void tira_bonus_palheta(PALHETA *pal);

void tira_bonus_pontos(TIJOLO listaTijolos[]);

void printa_bonus(BOLA objetobonus);

void animacao_winner();

void printa_score(JOGADOR score[]);

void desce_lista(int i, JOGADOR lista[]);

void sobe_lista(int i, JOGADOR lista[]);

int temNomeIgual(JOGADOR jog, JOGADOR lista[]);

void inserirJogador(int i, JOGADOR jog, JOGADOR lista[]);

void MostraListaJogadores(JOGADOR jog, JOGADOR score[]);

void OrdenaListaJogadores (JOGADOR  jog, JOGADOR lista[]);

void animacao_troca_fase(COLORS cor);

void pede_nome(JOGADOR *jog);
