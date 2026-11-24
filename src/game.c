#include "game.h"
#include "board.h"
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>

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
    *game = (Game){.current = game_spawn_piece()};
}

bool game_try_move(Game *game, int dx, int dy) {
    Piece next = game->current;
    next.x += dx;
    next.y += dy;
    if (board_collision(&game->board, &next)) {
        return false;
    }
    game->current = next;
    return true;
}

bool game_try_rotate(Game *game) {
    Piece next = game->current;
    piece_rotate(&next);
    if (board_collision(&game->board, &next)) {
        return false;
    }
    game->current = next;
    return true;
}

void game_soft_drop(Game *game) {
    if (game_try_move(game, 0, 1)) {
        game->drop_timer = 0.0f;
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
        game->score += POINTS_TIME_TICK;
    }

    if (game->drop_timer >= DROP_INTERVAL) {
        game->drop_timer -= DROP_INTERVAL;

        if (!game_try_move(game, 0, 1)) {
            board_fix_piece(&game->board, &game->current);
            game->score += POINTS_PIECE_LOCKED;

            int cleared = board_clear_rows(&game->board);
            if (cleared > 0) {
                game->score += cleared * POINTS_LINE_CLEARED;
            }

            game->current = game_spawn_piece();

            if (board_collision(&game->board, &game->current)) {
                game->game_over = true;
            }
        }
    }
}
