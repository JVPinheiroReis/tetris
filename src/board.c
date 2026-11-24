#include "board.h"
#include "config.h"
#include "piece.h"
#include <string.h>

void board_init(Board *board) {
    memset(board->cells, PIECE_NONE, sizeof(board->cells));
}

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
    int r, c, row;
    for (r = ROWS - 1; r >= 0; r--) {
        int full = 1;

        for (c = 0; c < COLUMNS; c++) {
            if (board->cells[r][c] == PIECE_NONE) {
                full = 0;
                break;
            }
        }

        if (full) {
            for (row = r; row >= 1; row--) {
                memcpy(board->cells[row],
                       board->cells[row - 1],
                       sizeof(board->cells[row]));
            }

            memset(board->cells[0], PIECE_NONE, sizeof(board->cells[0]));

            cleared++;
            r++;
        }
    }

    return cleared;
}