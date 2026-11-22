#include "render.h"
#include "board.h"
#include "config.h"
#include "game.h"
#include "piece.h"
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

static void render_draw_cell_lines(int r, int c) {
    DrawRectangleLines(c * CELL, r * CELL, CELL, CELL, LIGHTGRAY);
}

static void render_draw_cell(int r, int c, PieceType type) {
    DrawRectangle(
        c * CELL + 1, r * CELL + 1, CELL - 3, CELL - 3, PIECE_COLORS[type]);
    render_draw_cell_lines(r, c);
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

static void render_piece(const Piece *p, bool preview) {
    if (p->type == PIECE_NONE) return;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (!PIECE_SHAPES[p->type][p->rotation][r][c]) continue;

            int row = p->y + r;
            int col = p->x + c;
            if (row >= 0 && row < ROWS && col >= 0 && col < COLUMNS) {
                if (preview) {
                    render_draw_cell_lines(row, col);
                } else {
                    render_draw_cell(row, col, p->type);
                }
            }
        }
    }
}

static void render_current_piece_preview(const Board *board, const Piece *p) {
    if (p->type == PIECE_NONE) return;

    Piece pp = *p;
    if (board_collision(board, &pp)) return;

    while (!board_collision(board, &pp)) {
        piece_move_down(&pp);
    }
    piece_move_up(&pp);

    if (pp.y == p->y) return;
    render_piece(&pp, true);
}

void render_draw(const Game *game) {
    BeginDrawing();
    ClearBackground(BLACK);

    render_pieces(&game->board);
    render_current_piece_preview(&game->board, &game->current);
    render_piece(&game->current, false);

    DrawText(TextFormat("Score: %d", game->score), 10, 10, 20, YELLOW);
    DrawText(TextFormat("Time: %d", (int)game->elapsed), 10, 30, 20, YELLOW);

    EndDrawing();
}
