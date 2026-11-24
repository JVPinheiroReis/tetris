#include "game.h"
#include "board.h"
#include "config.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const char *game_instructions[INSTRUCTIONS_COUNT] = {
    "TETRIS 2.0",
    "",
    "",
    "Alguém um dia falou que um verdadeiro clássico nunca morre.",
    "",
    "",
    "Quem falou? Nem ideia.",
    "",
    "E se ninguém falou, deveria, porque o Tetris é um exemplo disso.",
    "",
    "",
    "Refizemos aquele tradicional dos anos 80, mas quem sabe, até melhor",
    "",
    "Para jogar é fácil:",
    "Seta para a esquerda / direita: mover a peça",
    "Seta para cima: rotacionar a peça",
    "Seta para baixo: descer a peça mais rápido",
    "Para ganhar, complete as linhas para ganhar pontos",
    "",
    "Partiu voltar no tempo e jogar um clássico revolucionário?",
    "",
    "Aperte ENTER e bom jogo..."};

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

int game_update(Game *game, float dt) {
    if (dt > MAX_DELTA_TIME) {
        dt = MAX_DELTA_TIME;
    }

    if (game->state == STATE_INTRO) {
        return 0;
    }

    if (game->state == STATE_GAME_OVER) {
        if (game->game_over_timer < GAME_OVER_DURATION) {
            game->game_over_timer += dt;
        }
        return 0;
    }

    game->elapsed += dt;
    game->score_timer += dt;
    game->drop_timer += dt;

    if (game->score_timer >= SCORE_INTERVAL) {
        game->score_timer -= SCORE_INTERVAL;
        game->score += POINTS_TIME_TICK;
    }

    int cleared = 0;

    if (game->drop_timer >= DROP_INTERVAL) {
        game->drop_timer -= DROP_INTERVAL;

        if (!game_try_move(game, 0, 1)) {
            board_fix_piece(&game->board, &game->current);
            game->score += POINTS_PIECE_LOCKED;

            cleared = board_clear_rows(&game->board);
            if (cleared > 0) {
                game->score += cleared * POINTS_LINE_CLEARED;
            }

            game->current = game_spawn_piece();

            if (board_collision(&game->board, &game->current)) {
                game->state = STATE_GAME_OVER;
                game_delete_save(SAVE_PATH);
            }
        }
    }

    return cleared;
}

bool game_save(const Game *game, const char *path) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        return false;
    }

    bool ok = fwrite(game, sizeof(*game), 1, f) == 1;
    fclose(f);
    return ok;
}

bool game_load(Game *game, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        return false;
    }

    bool ok = fread(game, sizeof(*game), 1, f) == 1;
    fclose(f);
    return ok;
}

void game_delete_save(const char *path) {
    remove(path);
}
