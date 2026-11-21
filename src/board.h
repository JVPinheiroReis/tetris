#ifndef BOARD_H
#define BOARD_H

#include "config.h"
#include "piece.h"

typedef struct {
    int cells[LINES][COLUMNS];
} Board;

void board_init(Board *board);
int board_is_free(const Board *board, int lin, int col);
int board_collision(const Board *board, const Piece *p);
void board_fix_piece(Board *board, const Piece *p);
int board_clear_lines(Board *board);

#endif
