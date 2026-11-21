#include "game.h"

void game_init(Game *game) {
    board_init(&game->board);
    game->current = (Piece){0};
    game->score = 0;
    game->timer = 0.0f;

    // game->board.cells[3][3] = 1;
    // game->board.cells[4][3] = 1;
    // game->board.cells[4][4] = 1;
}

void game_update(Game *game, float dt) {
    game->timer += dt;
    if (game->timer >= DROP_INTERVAL) {
        game->timer -= DROP_INTERVAL;
        piece_move_down(&game->current);
    }
}
