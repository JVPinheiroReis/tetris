#include "piece.h"

void piece_move_down(Piece *p) {
    p->y++;
}

void piece_move_left(Piece *p) {
    p->x--;
}

void piece_move_right(Piece *p) {
    p->x++;
}