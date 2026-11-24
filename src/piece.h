#ifndef PIECE_H
#define PIECE_H

#include "config.h"

typedef enum {
    PIECE_NONE = 0,
    PIECE_I,
    PIECE_O,
    PIECE_T,
    PIECE_S,
    PIECE_Z,
    PIECE_J,
    PIECE_L,
    PIECE_COUNT
} PieceType;

typedef enum { ROT_0 = 0, ROT_90, ROT_180, ROT_270, ROT_COUNT } Rotation;

extern const int PIECE_SHAPES[PIECE_COUNT][ROT_COUNT][PIECE_SIZE][PIECE_SIZE];

typedef struct {
    int row;
    int col;
} Position;

typedef struct {
    PieceType type;
    int x;
    int y;
    int rotation;
} Piece;

void piece_move_up(Piece *p);
void piece_move_down(Piece *p);
void piece_move_left(Piece *p);
void piece_move_right(Piece *p);
void piece_rotate(Piece *p);
void piece_undo_rotate(Piece *p);

#endif
