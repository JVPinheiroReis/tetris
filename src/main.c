#include "config.h"
#include "game.h"
#include "raylib.h"
#include "render.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();

    Music bgm = LoadMusicStream(BGM_PATH);
    bool has_bgm = IsMusicValid(bgm);
    if (has_bgm) {
        SetMusicVolume(bgm, BGM_VOLUME);
        PlayMusicStream(bgm);
    }

    SetTargetFPS(TARGET_FPS);

    Game game;
    game_init(&game);

    while (!WindowShouldClose()) {
        if (game.state == STATE_INTRO) {
            if (IsKeyPressed(KEY_ENTER)) {
                game.state = STATE_PLAYING;
            }
        }
        else if (game.state == STATE_GAME_OVER) {
            if (has_bgm && IsMusicStreamPlaying(bgm)) {
                PauseMusicStream(bgm);
            }

            if (IsKeyPressed(KEY_ENTER)) {
                game_init(&game);
                game.state = STATE_PLAYING;
                if (has_bgm) {
                    StopMusicStream(bgm);
                    PlayMusicStream(bgm);
                }
            }
            else if (IsKeyPressed(KEY_N)) {
                break;
            }
        }
        else {
            if (has_bgm) {
                UpdateMusicStream(bgm);
            }

            if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
                game_try_move(&game, -1, 0);
            }

            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
                game_try_move(&game, 1, 0);
            }

            if (IsKeyPressed(KEY_UP)) {
                game_try_rotate(&game);
            }

            if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
                game_soft_drop(&game);
            }
        }

        game_update(&game, GetFrameTime());
        render_draw(&game);
    }

    if (has_bgm) {
        UnloadMusicStream(bgm);
    }
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
