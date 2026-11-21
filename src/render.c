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

static void render_draw_cell(int r, int c, PieceType type) {
    DrawRectangle(
        c * CELL + 1, r * CELL + 1, CELL - 3, CELL - 3, PIECE_COLORS[type]);
    DrawRectangleLines(c * CELL, r * CELL, CELL, CELL, LIGHTGRAY);
}

static void render_pieces(const Board *board) {
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLUMNS; c++) {
            PieceType type = board->cells[r][c];
            if (type == PIECE_NONE) continue;

            render_draw_cell(r, c, type);
        }
    }
}

static void render_current_piece(const Piece *p) {
    int r, c;
    if (p->type == PIECE_NONE) return;
    for (r = 0; r < 4; r++) {
        for (c = 0; c < 4; c++) {
            if (!PIECE_SHAPES[p->type][p->rotation][r][c]) continue;

            int row = p->y + r;
            int col = p->x + c;
            if (row >= 0 && row < ROWS && col >= 0 && col < COLUMNS) {
                render_draw_cell(row, col, p->type);
            }
        }
    }
}

void render_draw(const Game *game) {
    BeginDrawing();
    ClearBackground(BLACK);

    render_pieces(&game->board);
    render_current_piece(&game->current);

    DrawText(TextFormat("Score: %d", game->score), 10, 10, 20, YELLOW);
    DrawText(TextFormat("Time: %d", (int)game->elapsed), 10, 30, 20, YELLOW);

    EndDrawing();
}
