#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "piece.h"
#include <stdbool.h>

// Instrucoes mostradas no inicio do jogo (uma string por linha)
#define INSTRUCTIONS_COUNT 23
extern const char *game_instructions[INSTRUCTIONS_COUNT];

typedef enum {
    STATE_INTRO = 0,
    STATE_PLAYING,
    STATE_GAME_OVER
} GameState;

typedef struct {
    Board board;
    Piece current;
    GameState state;
    int score;
    float elapsed;         // tempo total de jogo em segundos
    float drop_timer;      // tempo para queda da peca
    float score_timer;     // acumula ate 1s para pontuar por tempo
    float game_over_timer; // tempo decorrido na tela de game over
} Game;

void game_init(Game *game);
int game_update(Game *game, float dt);
bool game_try_move(Game *game, int dx, int dy);
bool game_try_rotate(Game *game);
void game_soft_drop(Game *game);
bool game_save(const Game *game, const char *path);
bool game_load(Game *game, const char *path);
void game_delete_save(const char *path);

#endif
