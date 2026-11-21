#include "render.h"
#include "game.h"
#include "raylib.h"

static const Color PIECE_COLORS[PIECE_COUNT] = {
    [PIECE_NONE] = BLACK,
    [PIECE_I] = SKYBLUE,
    [PIECE_O] = YELLOW,
    [PIECE_T] = PURPLE,
    [PIECE_S] = GREEN,
    [PIECE_Z] = RED,
    [PIECE_J] = BLUE,
    [PIECE_L] = ORANGE,
};

static void render_pieces(const Board *board) {
    int l, c;
    for (l = 0; l < LINES; l++) {
        for (c = 0; c < COLUMNS; c++) {
            PieceType type = board->cells[l][c];
            if (type == PIECE_NONE) continue;

            DrawRectangle(c * CELL + 1,
                          l * CELL + 1,
                          CELL - 3,
                          CELL - 3,
                          PIECE_COLORS[type]);
            DrawRectangleLines(c * CELL, l * CELL, CELL, CELL, LIGHTGRAY);
        }
    }
}

void render_draw(const Game *game) {
    BeginDrawing();
    ClearBackground(BLACK);

    render_pieces(&game->board);

    DrawText(TextFormat("Score: %d", game->score), 10, 10, 20, YELLOW);
    EndDrawing();
}
