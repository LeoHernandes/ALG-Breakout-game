short testa_colisao(int x1Obj1, int x2Obj1, int y1Obj1, int y2Obj1, int x1Obj2, int x2Obj2, int y1Obj2, int y2Obj2);

void move_palheta(char tecla, PALHETA *pal);

void bolinha_inicial(BOLA *bol, char tecla, FASE fase);

void colisao_bolinha_palheta(BOLA *bol, PALHETA pal);

void colisao_bolinha_moldura(BOLA *bol, JOGADOR *jog, PALHETA pal);

void colisao_bolinha_tijolo(TIJOLO tij, BOLA *bol);

int testa_colisao_bolinha_tijolo(TIJOLO listatijolos[], BOLA *bol);

void move_bolinha(BOLA *bol, PALHETA *pal, JOGADOR *jog, TIJOLO listaTijolos[], int *indiceTij);

void perde_vida_bolinha(BOLA *bol, JOGADOR *jog, PALHETA *pal);

int move_bonus(TIJOLO listatijolo[], TIJOLO tijolodestruido, BOLA *objetobonus, PALHETA *pal, JOGADOR *jog, FASE level[]);
