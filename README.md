# Tetris

Essa é uma versão para Linux do jogo Tetris(1984).

A única linguagem utilizada é C, enquanto as bibliotecas são `raylib`, `math` e a biblioteca padrão da linguagem C.

## Estrutura de arquivos

```txt
tetris/
├── Makefile
├── libs/raylib     # biblioteca compilada estaticamente
└── src/
    ├── main.c      # loop princial do jogo
    ├── config.h    # constantes (CELULA, COLUNAS, LINHAS, tempos)
    ├── board.h
    ├── board.c     # matriz do tabuleiro / colisão 
    ├── piece.h
    ├── piece.c     # formatos das peças / movimento
    ├── game.h
    ├── game.c      # estado do jogo / regras
    ├── render.h
    └── render.c    # parte de renderização (raylib)
```

## Instalação

Primeiramente, é preciso que todas as dependências do `raylib` estejam instaladas (ver <https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux>).

1. Use o comando `make` para compilar o jogo
2. Permita a execução:  `chmod +x ./tetris`
3. Execute `./tetris`
