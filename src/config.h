#ifndef CONFIG_H
#define CONFIG_H

// Janela e tabuleiro
#define WINDOW_TITLE "Tetris"
#define TARGET_FPS 60

#define CELL 30
#define COLUMNS 15
#define ROWS 20
#define WINDOW_WIDTH (COLUMNS * CELL)
#define WINDOW_HEIGHT (ROWS * CELL)

#define PIECE_SIZE 4

// Audio
#define BGM_PATH "resources/theme.mp3"
#define BGM_VOLUME 0.3f
#define GAME_OVER_BGM_PATH "resources/game_over.mp3"
#define GAME_OVER_BGM_VOLUME 0.3f
#define SFX_CLEAR_ROW_PATH "resources/clear_row.wav"
#define SFX_CLEAR_ROW_VOLUME 0.5f

// Tempos (em segundos)
#define DROP_INTERVAL 0.5f
#define SCORE_INTERVAL 1.0f
#define GAME_OVER_ROW_DELAY 0.10f
#define GAME_OVER_HOLD_DELAY 1.0f
#define GAME_OVER_DURATION (ROWS * GAME_OVER_ROW_DELAY + GAME_OVER_HOLD_DELAY)
#define MAX_DELTA_TIME 0.1f

// Pontuacao
#define POINTS_PIECE_LOCKED 10
#define POINTS_LINE_CLEARED 100
#define POINTS_TIME_TICK 1

// Persistencia
#define SAVE_PATH "save.dat"

#endif
