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
    render_init();
    InitAudioDevice();

    Music bgm = LoadMusicStream(BGM_PATH);
    bool has_bgm = IsMusicValid(bgm);
    if (has_bgm) {
        SetMusicVolume(bgm, BGM_VOLUME);
        PlayMusicStream(bgm);
    }

    Music game_over_bgm = LoadMusicStream(GAME_OVER_BGM_PATH);
    bool has_game_over_bgm = IsMusicValid(game_over_bgm);
    if (has_game_over_bgm) {
        SetMusicVolume(game_over_bgm, GAME_OVER_BGM_VOLUME);
    }

    Sound sfx_clear_row = LoadSound(SFX_CLEAR_ROW_PATH);
    bool has_sfx_clear_row = IsSoundValid(sfx_clear_row);
    if (has_sfx_clear_row) {
        SetSoundVolume(sfx_clear_row, SFX_CLEAR_ROW_VOLUME);
    }

    SetTargetFPS(TARGET_FPS);

    Game game;
    if (!game_load(&game, SAVE_PATH)) {
        game_init(&game);
    }

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

            if (has_game_over_bgm) {
                if (!IsMusicStreamPlaying(game_over_bgm)) {
                    PlayMusicStream(game_over_bgm);
                }
                UpdateMusicStream(game_over_bgm);
            }

            if (IsKeyPressed(KEY_ENTER)) {
                game_init(&game);
                game.state = STATE_PLAYING;
                if (has_game_over_bgm) {
                    StopMusicStream(game_over_bgm);
                }
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

        int cleared = game_update(&game, GetFrameTime());
        if (cleared > 0 && has_sfx_clear_row) {
            PlaySound(sfx_clear_row);
        }
        render_draw(&game);
    }

    if (game.state == STATE_PLAYING) {
        game_save(&game, SAVE_PATH);
    }

    if (has_sfx_clear_row) UnloadSound(sfx_clear_row);
    if (has_game_over_bgm) UnloadMusicStream(game_over_bgm);
    if (has_bgm) UnloadMusicStream(bgm);

    CloseAudioDevice();
    render_shutdown();
    CloseWindow();
    return 0;
}
