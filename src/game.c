#include "game.h"

const char *game_instructions[INSTRUCTIONS_COUNT] = {
    "TETRIS 2.0",
    "",
    "",
    "Alguem um dia falou que um verdadeiro classico nunca morre.",
    "",
    "",
    "Quem falou? Nem ideia.",
    "",
    "E se ninguem falou, deveria, porque o Tetris eh um exemplo disso.",
    "",
    "",
    "Refizemos aquele tradicional dos anos 80, mas quem sabe, ate melhor",
    "",
    "Para jogar eh facil:",
    "Seta esquerda / direita: mover a peca",
    "Seta para cima: rotacionar a peca",
    "Seta para baixo: descer a peca mais rapido",
    "Para ganhar vc completa linhas para ganhar pontos",
    "",
    "Partiu voltar no tempo e jogar um classico revolucionario?",
    "",
    "Aperte ENTER e bom jogo."
};

void game_init(Game *game) {
    board_init(&game->board);
    game->current = (Piece){0};
    game->score = 0;
    game->drop_timer = 0.0f;
    game->elapsed = 0.0f;
    game->score_timer = 0.0f;
}

void game_add_score(Game *game, ScoreEvent event, int amount) {
    switch (event) {
        case SCORE_PIECE_LOCKED: game->score += 10; break;
        case SCORE_LINES_CLEARED: game->score += amount * 100; break;
        case SCORE_TIME_TICK: game->score += 1; break;
    }
}

void game_update(Game *game, float dt) {
    // conta o tempo
    game->elapsed += dt;
    game->score_timer += dt;
    game->drop_timer += dt;

    if (game->score_timer >= 1.0f) {
        game->score_timer -= 1.0f; // pontos por tempo: 1 ponto a cada 1 segundo
        game_add_score(game, SCORE_TIME_TICK, 1);
    }

    if (game->drop_timer >= DROP_INTERVAL) {
        game->drop_timer -= DROP_INTERVAL;
        piece_move_down(&game->current);

        //  quando uma peça for fixada no tabuleiro:
        // game_add_score(game, SCORE_PIECE_LOCKED, 1);

        //  quando linhas forem completadas:
        // game_add_score(game, SCORE_LINES_CLEARED, numero_de_linhas);
    }
}
