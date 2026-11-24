#include "game.h"
#include "board.h"
#include "config.h"
#include <stdbool.h>
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
        .x = COLUMNS / 2 - PIECE_SIZE / 2,
        .y = 0,
        .rotation = 0,
    };
    return p;
}

void game_init(Game *game) {
    srand((unsigned int)time(NULL));
    board_init(&game->board);
    game->current = game_spawn_piece();
    game->game_over = false;
    game->score = 0;
    game->elapsed = 0.0f;
    game->drop_timer = 0.0f;
    game->score_timer = 0.0f;
    game->game_over_timer = 0.0f;
}

void game_add_score(Game *game, ScoreEvent event, int amount) {
    switch (event) {
        case SCORE_PIECE_LOCKED:
            game->score += amount * POINTS_PIECE_LOCKED;
            break;
        case SCORE_ROWS_CLEARED:
            game->score += amount * POINTS_LINE_CLEARED;
            break;
        case SCORE_TIME_TICK: game->score += amount * POINTS_TIME_TICK; break;
    }
}

void game_update(Game *game, float dt) {
    if (dt > MAX_DELTA_TIME) {
        dt = MAX_DELTA_TIME;
    }

    if (game->game_over) {
        if (game->game_over_timer < GAME_OVER_DURATION) {
            game->game_over_timer += dt;
        }
        return;
    }

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
            piece_move_up(&game->current);

            board_fix_piece(&game->board, &game->current);
            game_add_score(game, SCORE_PIECE_LOCKED, 1);

            int cleared = board_clear_rows(&game->board);
            if (cleared > 0) {
                game_add_score(game, SCORE_ROWS_CLEARED, cleared);
            }

            game->current = game_spawn_piece();

            if (board_collision(&game->board, &game->current)) {
                game->game_over = true;
            }
        }
    }
}
