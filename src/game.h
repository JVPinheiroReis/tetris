// molde de pontualao
// tudo q precisar ser lembrado fica na struct game
// padrao eh rodar 60x por seg
// Para dar 1 ponto a cada 1 seg real, é preciso um cronom.
// que vai somando os dt de varios frames atechegar a 1.0

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "piece.h"

typedef enum {
    SCORE_PIECE_LOCKED,  // uma peca foi fixada
    SCORE_LINES_CLEARED, // linhas completadas
    SCORE_TIME_TICK      // passou 1 seg
} ScoreEvent;

typedef struct {
    Board board;
    Piece current;
    int score;
    float elapsed; // tempo total de jogo em seg(to fazendo em ingles pra vc n
                   // reclamar)
    float drop_timer;  // tempo para queda da piece
    float score_timer; // acumula até 1s para pontuar por tempo
} Game;

void game_init(Game *game);
void game_update(Game *game, float dt);
void game_add_score(Game *game, ScoreEvent event, int amount);

// instrucoes mostradas no inicio do jogo (uma string por linha)
#define INSTRUCTIONS_COUNT 22
extern const char *game_instructions[INSTRUCTIONS_COUNT];

#endif
