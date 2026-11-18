#include "board.h"
#include <string.h>

void board_init(Board *board) {
    memset(board->cells, 0, sizeof(board->cells));
}
