#include "config.h"
#include "game.h"
#include "raylib.h"
#include "render.h"

int main(void) {
    InitWindow(COLUMNS * CELL, LINES * CELL, "Tetris");
    SetTargetFPS(60);

    Game game;
    game_init(&game);

    while (!WindowShouldClose()) {
        game_update(&game, GetFrameTime());
        render_draw(&game);

        if (IsKeyPressed(KEY_LEFT)) {
            piece_move_left(&game.current);
            if (board_collision(&game.board, &game.current)) {
                piece_move_right(&game.current);
            }
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            piece_move_right(&game.current);
            if (board_collision(&game.board, &game.current)) {
                piece_move_left(&game.current);
            }
        }
        if (IsKeyPressed(KEY_UP)) {
            piece_rotate(&game.current);
            if (board_collision(&game.board, &game.current)) {
                piece_undo_rotate(&game.current);
            }
        }
        if (IsKeyPressed(KEY_DOWN)) {
            piece_move_down(&game.current);
            if (board_collision(&game.board, &game.current)) {
                game.current.y--;
            }
        }
    }

    CloseWindow();
    return 0;
}
