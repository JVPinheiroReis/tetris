#include "game.h"
#include "board.h"
#include "config.h"
#include <stdlib.h>
#include <time.h>

const char *game_instructions[INSTRUCTIONS_COUNT] = {
    "TETRIS 2.0",
    "",
    "",
    "Alguem um dia falou que um verdadeiro classico nunca morre.",
    "",
    "",
    "Quem falou? Nem ideia.",
    "",
    "E se ninguem falou, deveria, porque o Tetris eh um exemplo disso.",
    "",
    "",
    "Refizemos aquele tradicional dos anos 80, mas quem sabe, ate melhor",
    "",
    "Para jogar eh facil:",
    "Seta esquerda / direita: mover a peca",
    "Seta para cima: rotacionar a peca",
    "Seta para baixo: descer a peca mais rapido",
    "Para ganhar vc completa linhas para ganhar pontos",
    "",
    "Partiu voltar no tempo e jogar um classico revolucionario?",
    "",
    "Aperte ENTER e bom jogo."};

static Piece game_spawn_piece(void) {
    Piece p = {
        .type = (PieceType)(1 + rand() % (PIECE_COUNT - 1)),
        .x = COLUMNS / 2 - 2,
        .y = 0,
        .rotation = 0,
    };
    return p;
}

void game_init(Game *game) {
    srand((unsigned int)time(NULL));
    board_init(&game->board);
    game->current = game_spawn_piece();
    game->score = 0;
    game->elapsed = 0.0f;
    game->drop_timer = 0.0f;
    game->score_timer = 0.0f;
}

void game_add_score(Game *game, ScoreEvent event, int amount) {
    switch (event) {
        case SCORE_PIECE_LOCKED: game->score += 10; break;
        case SCORE_ROWS_CLEARED: game->score += amount * 100; break;
        case SCORE_TIME_TICK: game->score += 1; break;
    }
}

void game_update(Game *game, float dt) {
    game->elapsed += dt;
    game->score_timer += dt;
    game->drop_timer += dt;

    if (game->score_timer >= SCORE_INTERVAL) {
        game->score_timer -= SCORE_INTERVAL;
        game_add_score(game, SCORE_TIME_TICK, 1);
    }

    if (game->drop_timer >= DROP_INTERVAL) {
        game->drop_timer -= DROP_INTERVAL;
        piece_move_down(&game->current);
        if (board_collision(&game->board, &game->current)) {
            game->current.y--;
            board_fix_piece(&game->board, &game->current);
            game_add_score(game, SCORE_PIECE_LOCKED, 1);

            int cleared = board_clear_rows(&game->board);
            if (cleared > 0) {
                game_add_score(game, SCORE_ROWS_CLEARED, cleared);
            }

            game->current = game_spawn_piece();
        }
    }
}
