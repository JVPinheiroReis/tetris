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

static void render_draw_cell(int l, int c, PieceType type) {
    DrawRectangle(
        c * CELL + 1, l * CELL + 1, CELL - 3, CELL - 3, PIECE_COLORS[type]);
    DrawRectangleLines(c * CELL, l * CELL, CELL, CELL, LIGHTGRAY);
}

static void render_pieces(const Board *board) {
    int l, c;
    for (l = 0; l < LINES; l++) {
        for (c = 0; c < COLUMNS; c++) {
            PieceType type = board->cells[l][c];
            if (type == PIECE_NONE) continue;
            render_draw_cell(l, c, type);
        }
    }
}

static void render_current_piece(const Piece *p) {
    if (p->type == PIECE_NONE) return;
    for (int i = 0; i < 4; i++) {
        Position block = PIECE_SHAPES[p->type][p->rotation][i];
        int l = p->y + block.lin;
        int c = p->x + block.col;
        if (l >= 0 && l < LINES && c >= 0 && c < COLUMNS) {
            render_draw_cell(l, c, p->type);
        }
    }
}

void render_draw(const Game *game) {
    BeginDrawing();
    ClearBackground(BLACK);

    render_pieces(&game->board);
    render_current_piece(&game->current);

    DrawText(TextFormat("Score: %d", game->score), 10, 10, 20, YELLOW);
    EndDrawing();
}
