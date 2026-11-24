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

// Tempos (em segundos)
#define DROP_INTERVAL 0.5f
#define SCORE_INTERVAL 1.0f
#define GAME_OVER_ROW_DELAY 0.05f
#define GAME_OVER_DURATION (ROWS * GAME_OVER_ROW_DELAY)

// Pontuacao
#define POINTS_PIECE_LOCKED 10
#define POINTS_LINE_CLEARED 100
#define POINTS_TIME_TICK 1

#endif
