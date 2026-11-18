#include "render.h"
#include "raylib.h"

static const Color PIECE_COLORS[PIECE_COUNT] = {
    [PIECE_NONE] = BLACK,
    [PIECE_I] = SKYBLUE,
    [PIECE_O] = YELLOW,
    [PIECE_T] = PURPLE,
    [PIECE_S] = GREEN,
    [PIECE_Z] = RED,
    [PIECE_J] = BLUE,
    [PIECE_L] = ORANGE,
};

void render_draw(const Game *game) {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    EndDrawing();
}
