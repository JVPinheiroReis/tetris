#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "Teste raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("raylib funcionando!", 220, 200, 30, YELLOW);
        DrawRectangle(350, 260, 60, 60, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}