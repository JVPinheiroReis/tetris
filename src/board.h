#ifndef BOARD_H
#define BOARD_H

#include "config.h"

typedef struct {
    int cells[LINES][COLUMNS];
} Board;

void board_init(Board *board);

#endif
