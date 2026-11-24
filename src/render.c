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

    int r, c;
    for (r = 0; r < PIECE_SIZE; r++) {
        for (c = 0; c < PIECE_SIZE; c++) {
            if (!PIECE_SHAPES[p->type][p->rotation][r][c]) continue;

            int row = p->y + r;
            int col = p->x + c;
            if (row >= 0 && row < ROWS && col >= 0 && col < COLUMNS) {
                if (preview) {
                    render_draw_cell_lines(row, col);
                }
                else {
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

static void render_centered_text(const char *text, int y, int font_size,
                                 Color color) {
    int x = (WINDOW_WIDTH - MeasureText(text, font_size)) / 2;
    DrawText(text, x, y, font_size, color);
}

static void render_game_over(const Game *game) {
    bool anim_done = game->game_over_timer >= GAME_OVER_DURATION;
    if (!anim_done) {
        int rows = (int)(game->game_over_timer / GAME_OVER_ROW_DELAY);
        render_pieces(&game->board);
        DrawRectangle(0, 0, WINDOW_WIDTH, rows * CELL, BLACK);
    }

    render_centered_text("Game", 50, 80, RED);
    render_centered_text("Over", 140, 80, RED);

    if (anim_done) {
        render_centered_text(
            TextFormat("Score: %d", game->score), 260, 30, YELLOW);
        render_centered_text("Continuar?", 320, 30, WHITE);
        render_centered_text("[ENTER] Sim   [N] Nao", 370, 24, LIGHTGRAY);
    }
}

void render_draw(const Game *game) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (game->game_over) {
        render_game_over(game);
    }
    else {
        render_pieces(&game->board);
        render_current_piece_preview(&game->board, &game->current);
        render_piece(&game->current, false);

        DrawText(TextFormat("Score: %d", game->score), 10, 10, 20, YELLOW);
        DrawText(
            TextFormat("Time: %d", (int)game->elapsed), 10, 30, 20, YELLOW);
    }

    EndDrawing();
}