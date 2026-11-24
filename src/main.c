#include "config.h"
#include "game.h"
#include "piece.h"
#include "raylib.h"
#include "render.h"

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();

    Music bgm = LoadMusicStream(BGM_PATH);
    SetMusicVolume(bgm, BGM_VOLUME);
    PlayMusicStream(bgm);

    SetTargetFPS(TARGET_FPS);

    Game game;
    game_init(&game);

    while (!WindowShouldClose()) {
        if (game.game_over) {
            if (IsMusicStreamPlaying(bgm)) {
                PauseMusicStream(bgm);
            }

            if (IsKeyPressed(KEY_ENTER)) {
                game_init(&game);
                StopMusicStream(bgm);
                PlayMusicStream(bgm);
            }
            else if (IsKeyPressed(KEY_N)) {
                break;
            }
        }
        else {
            UpdateMusicStream(bgm);

            if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
                piece_move_left(&game.current);
                if (board_collision(&game.board, &game.current)) {
                    piece_move_right(&game.current);
                }
            }

            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
                piece_move_right(&game.current);
                if (board_collision(&game.board, &game.current)) {
                    piece_move_left(&game.current);
                }
            }

            if (IsKeyPressed(KEY_UP)) {
                piece_rotate(&game.current);
                if (board_collision(&game.board, &game.current)) {
                    piece_undo_rotate(&game.current);
                }
            }

            if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
                piece_move_down(&game.current);
                if (board_collision(&game.board, &game.current)) {
                    piece_move_up(&game.current);
                }
            }
        }

        game_update(&game, GetFrameTime());
        render_draw(&game);
    }

    UnloadMusicStream(bgm);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
