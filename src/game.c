#include "game.h"

void game_init(Game *game) {
    board_init(&game->board);
    game->current = (Piece){0};
    game->score = 0;
    game->drop_timer = 0.0f;
    game->elapsed = 0.0f;
    game->score_timer = 0.0f;

    // game->board.cells[3][3] = 1;
    // game->board.cells[4][3] = 1;
    // game->board.cells[4][4] = 1;
}

void game_add_score(Game *game, ScoreEvent event, int amount) {
    switch (event) {
        case SCORE_PIECE_LOCKED:
            game->score += 10;
            break;
        case SCORE_LINES_CLEARED:
            game->score += amount * 100;
            break;
        case SCORE_TIME_TICK:
            game->score += 1;
            break;
    }
}

void game_update(Game *game, float dt) {
    // conta o tempo
    game->elapsed     += dt;
    game->score_timer += dt;
    game->drop_timer  += dt;

    // pontos por tempo: 1 ponto a cada 1 segundo
    if (game->score_timer >= 1.0f) {
        game->score_timer -= 1.0f;
        game_add_score(game, SCORE_TIME_TICK, 1);
    }

    // queda da peça (código que já existia)
    if (game->drop_timer >= DROP_INTERVAL) {
        game->drop_timer -= DROP_INTERVAL;
        piece_move_down(&game->current);

        // TODO: quando uma peça for fixada no tabuleiro:
        // game_add_score(game, SCORE_PIECE_LOCKED, 1);

        // TODO: quando linhas forem completadas:
        // game_add_score(game, SCORE_LINES_CLEARED, numero_de_linhas);
    }
}
