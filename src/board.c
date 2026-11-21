#include "board.h"
#include "config.h"
#include "piece.h"
#include <string.h>

void board_init(Board *board) {
    memset(board->cells, 0, sizeof(board->cells));
}

int board_is_free(const Board *board, int lin, int col) {
    if (lin < 0 || lin >= LINES || col < 0 || col >= COLUMNS) {
        return 0;
    }
    if (board->cells[lin][col] == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int board_collision(const Board *board, const Piece *p) {
    int line, column;
    int i;
    for (i = 0; i < 4; i++) {
        Position block = PIECE_SHAPES[p->type][p->rotation][i];

        line = p->y + block.lin;
        column = p->x + block.col;

        if (board_is_free(board, line, column) == 0) {
            return 1;
        }
    }
    return 0;
}

void board_fix_piece(Board *board, const Piece *p) {
    int i;
    for (i = 0; i < 4; i++) {
        Position block = PIECE_SHAPES[p->type][p->rotation][i];

        int line = p->y + block.lin;
        int column = p->x + block.col;

        if (line >= 0 && line < LINES && column >= 0 && column < COLUMNS) {
            board->cells[line][column] = p->type;
        }
    }
}

int board_clear_lines(Board *board) {
    int cleared = 0;
    for (int l = LINES - 1; l >= 0; l--) {
        int full = 1;
        for (int c = 0; c < COLUMNS; c++) {
            if (board->cells[l][c] == 0) {
                full = 0;
                break;
            }
        }
        if (full) {
            for (int row = l; row > 0; row--) {
                memcpy(board->cells[row],
                       board->cells[row - 1],
                       sizeof(board->cells[row]));
            }
            memset(board->cells[0], 0, sizeof(board->cells[0]));
            cleared++;
            l++;
        }
    }
    return cleared;
}