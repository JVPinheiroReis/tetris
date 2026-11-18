#ifndef PIECE_H
#define PIECE_H

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

typedef struct {
    PieceType type;
    int x;
    int y;
    int rotation;
} Piece;

void piece_move_down(Piece *p);
void piece_move_left(Piece *p);
void piece_move_right(Piece *p);

#endif
