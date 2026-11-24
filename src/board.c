#include "board.h"
#include "config.h"
#include "piece.h"
#include <stdbool.h>
#include <string.h>

bool board_is_free(const Board *board, int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLUMNS) {
        return false;
    }

    return board->cells[row][col] == PIECE_NONE;
}

bool board_collision(const Board *board, const Piece *p) {
    int r, c;
    for (r = 0; r < PIECE_SIZE; r++) {
        for (c = 0; c < PIECE_SIZE; c++) {
            if (!PIECE_SHAPES[p->type][p->rotation][r][c]) continue;

            if (!board_is_free(board, p->y + r, p->x + c)) {
                return true;
            }
        }
    }
    return false;
}

void board_fix_piece(Board *board, const Piece *p) {
    int r, c;
    for (r = 0; r < PIECE_SIZE; r++) {
        for (c = 0; c < PIECE_SIZE; c++) {
            if (!PIECE_SHAPES[p->type][p->rotation][r][c]) continue;

            int row = p->y + r;
            int column = p->x + c;

            if (row >= 0 && row < ROWS && column >= 0 && column < COLUMNS) {
                board->cells[row][column] = p->type;
            }
        }
    }
}

int board_clear_rows(Board *board) {
    int cleared = 0;
    int r, c;
    for (r = ROWS - 1; r >= 0; r--) {
        bool full = true;

        for (c = 0; c < COLUMNS; c++) {
            if (board->cells[r][c] == PIECE_NONE) {
                full = false;
                break;
            }
        }

        if (full) {
            if (r > 0) {
                memmove(&board->cells[1],
                        &board->cells[0],
                        (size_t)r * sizeof(board->cells[0]));
            }

            memset(board->cells[0], 0, sizeof(board->cells[0]));

            cleared++;
            r++;
        }
    }

    return cleared;
}