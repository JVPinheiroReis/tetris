#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "piece.h"

typedef struct {
    Board board;
    Piece current;
    int score;
    float timer;
} Game;

void game_init(Game *game);
void game_update(Game *game, float dt);

#endif
