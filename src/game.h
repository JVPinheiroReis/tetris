#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "piece.h"
#include <stdbool.h>

// Instrucoes mostradas no inicio do jogo (uma string por linha)
#define INSTRUCTIONS_COUNT 22
extern const char *game_instructions[INSTRUCTIONS_COUNT];

typedef struct {
    Board board;
    Piece current;
    bool game_over;
    int score;
    float elapsed;         // tempo total de jogo em segundos
    float drop_timer;      // tempo para queda da peca
    float score_timer;     // acumula ate 1s para pontuar por tempo
    float game_over_timer; // tempo decorrido na tela de game over
} Game;

void game_init(Game *game);
void game_update(Game *game, float dt);

#endif
