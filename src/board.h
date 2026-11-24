#ifndef BOARD_H
#define BOARD_H

#include "config.h"
#include "piece.h"
#include <stdbool.h>

typedef struct {
    PieceType cells[ROWS][COLUMNS];
} Board;

void board_init(Board *board);
bool board_is_free(const Board *board, int row, int col);
bool board_collision(const Board *board, const Piece *p);
void board_fix_piece(Board *board, const Piece *p);
int board_clear_rows(Board *board);

#endif
