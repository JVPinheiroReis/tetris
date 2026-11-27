#include "render.h"
#include "board.h"
#include "config.h"
#include "game.h"
#include "piece.h"
#include "raylib.h"
#include <stddef.h>

static Font font;

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

static const int SKULL_SHAPE[ROWS][COLUMNS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

static void render_text(const char *text, int x, int y, int size, Color color) {
    DrawTextEx(font, text, (Vector2){x, y}, size, FONT_SPACING, color);
}

static void render_centered_text(const char *text, int y, int size,
                                 Color color) {
    int w = MeasureTextEx(font, text, size, FONT_SPACING).x;
    render_text(text, (WINDOW_WIDTH - w) / 2, y, size, color);
}

static void render_instructions(void) {
    render_centered_text("TETRIS 2.0", 36, FONT_SIZE_LARGE, YELLOW);
    DrawLine(40, 112, WINDOW_WIDTH - 40, 112, DARKGRAY);

    render_centered_text(
        "Alguém um dia falou que um", 140, FONT_SIZE_SMALL, WHITE);
    render_centered_text(
        "verdadeiro clássico nunca morre.", 170, FONT_SIZE_SMALL, WHITE);

    render_centered_text("Quem falou? Nem ideia.", 220, FONT_SIZE_SMALL, WHITE);

    render_centered_text(
        "E se ninguém falou, deveria,", 270, FONT_SIZE_SMALL, WHITE);
    render_centered_text(
        "porque o Tetris é um exemplo disso.", 300, FONT_SIZE_SMALL, WHITE);

    render_centered_text(
        "Refizemos aquele tradicional dos", 350, FONT_SIZE_SMALL, WHITE);
    render_centered_text(
        "anos 80, mas quem sabe, até melhor.", 380, FONT_SIZE_SMALL, WHITE);

    render_centered_text("Para jogar é fácil:", 440, FONT_SIZE_MEDIUM, SKYBLUE);
    render_centered_text(
        "Esquerda / Direita: mover a peça", 480, FONT_SIZE_SMALL, LIGHTGRAY);
    render_centered_text(
        "Cima: rotacionar a peça", 510, FONT_SIZE_SMALL, LIGHTGRAY);
    render_centered_text(
        "Baixo: descer mais rápido", 540, FONT_SIZE_SMALL, LIGHTGRAY);
    render_centered_text(
        "Complete linhas para pontuar", 570, FONT_SIZE_SMALL, LIGHTGRAY);
    render_centered_text(
        "Fechar o jogo salva seu progresso", 600, FONT_SIZE_SMALL, LIGHTGRAY);

    render_centered_text(
        "Partiu voltar no tempo e jogar", 660, FONT_SIZE_SMALL, WHITE);
    render_centered_text(
        "um clássico revolucionário?", 690, FONT_SIZE_SMALL, WHITE);

    DrawLine(40,
             WINDOW_HEIGHT - 96,
             WINDOW_WIDTH - 40,
             WINDOW_HEIGHT - 96,
             DARKGRAY);
    render_centered_text("Aperte ENTER e bom jogo...",
                         WINDOW_HEIGHT - 74,
                         FONT_SIZE_MEDIUM,
                         YELLOW);
}

static void render_draw_skull_transition(const Board *board, int rows) {
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLUMNS; c++) {
            if (r < rows) {
                if (SKULL_SHAPE[r][c]) {
                    DrawRectangle(
                        c * CELL + 1, r * CELL + 1, CELL - 3, CELL - 3, WHITE);
                    render_draw_cell_lines(r, c);
                }
            }
            else {
                PieceType type = board->cells[r][c];
                if (type != PIECE_NONE) {
                    render_draw_cell(r, c, type);
                }
            }
        }
    }
}

static void render_game_over(const Game *game) {
    if (game->game_over_timer < GAME_OVER_DURATION) {
        int rows = (int)(game->game_over_timer / GAME_OVER_ROW_DELAY);
        if (rows > ROWS) rows = ROWS;
        render_draw_skull_transition(&game->board, rows);
        return;
    }

    render_centered_text("Game", 50, FONT_SIZE_LARGE, RED);
    render_centered_text("Over", 130, FONT_SIZE_LARGE, RED);
    render_centered_text(
        TextFormat("Score: %d", game->score), 260, FONT_SIZE_MEDIUM, YELLOW);
    render_centered_text(TextFormat("Time: %d", (int)game->elapsed),
                         300,
                         FONT_SIZE_MEDIUM,
                         YELLOW);

    render_centered_text("Continuar?", 360, FONT_SIZE_MEDIUM, WHITE);
    render_centered_text(
        "[ENTER] Sim   [N] Nao", 400, FONT_SIZE_MEDIUM, LIGHTGRAY);
}

void render_init(void) {
    font = LoadFontEx(FONT_PATH, FONT_SIZE_LARGE, NULL, 224);
    if (!IsFontValid(font)) font = GetFontDefault();
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
}

void render_shutdown(void) {
    UnloadFont(font);
}

void render_draw(const Game *game) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (game->state == STATE_INTRO) {
        render_instructions();
    }
    else if (game->state == STATE_GAME_OVER) {
        render_game_over(game);
    }
    else {
        render_pieces(&game->board);
        render_current_piece_preview(&game->board, &game->current);
        render_piece(&game->current, false);

        render_text(TextFormat("Score: %d", game->score),
                    10,
                    10,
                    FONT_SIZE_SMALL,
                    YELLOW);
        render_text(TextFormat("Time: %d", (int)game->elapsed),
                    10,
                    35,
                    FONT_SIZE_SMALL,
                    YELLOW);
    }

    EndDrawing();
}