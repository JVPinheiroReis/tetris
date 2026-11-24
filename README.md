# Tetris

## Proposta

Esta é uma implementação para Linux do clássico jogo **Tetris (1984)**, desenvolvida integralmente em linguagem C. O projeto recria a experiência tradicional do jogo com interface gráfica, trilha sonora, efeitos sonoros e persistência automática de partidas.

## Principais funcionalidades

- **Mecânica clássica de Tetris:** movimentação lateral, rotação de peças, queda rápida (*soft drop*) e remoção automática de linhas completas.
- **Sistema de pontuação:** pontuação acumulada por tempo de sobrevivência, peças fixadas e linhas eliminadas.
- **Telas de fluxo do jogo:** tela inicial com instruções, partida ativa e animação de *Game Over* com opção de reiniciar ou sair.
- **Áudio integrado:** música de fundo durante a partida, música de *Game Over* e efeito sonoro ao completar linhas.
- **Persistência automática:** o progresso da partida é salvo automaticamente ao fechar o jogo e restaurado na próxima execução.

## Tecnologias utilizadas

- **Linguagem:** C (padrão C11)
- **Bibliotecas:** [raylib](https://www.raylib.com/) (gráficos e áudio, incluída compilada estaticamente em `libs/raylib`), biblioteca matemática (`libm`) e biblioteca padrão da linguagem C.
- **Build:** `gcc` e `make`

## Estrutura de arquivos

```txt
tetris/
├── Makefile        # configuração do processo de compilação
├── libs/raylib     # biblioteca compilada estaticamente
├── resources/      # músicas e efeitos sonoros
└── src/
    ├── main.c      # loop principal do jogo
    ├── config.h    # constantes (CELULA, COLUNAS, LINHAS, tempos)
    ├── board.h
    ├── board.c     # matriz do tabuleiro / colisão
    ├── piece.h
    ├── piece.c     # formatos das peças / movimento
    ├── game.h
    ├── game.c      # estado do jogo / regras / persistência de dados
    ├── render.h
    └── render.c    # parte de renderização (raylib)
```

## Instalação, compilação e execução

### 1. Dependências

Como o `raylib` já está incluído estaticamente no repositório, basta garantir que o compilador (`gcc`, `make`) e as dependências de sistema do `raylib` (OpenGL / X11) estejam instaladas no Linux (consulte <https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux> para detalhes):

- **Ubuntu / Debian:**

  ```bash
  sudo apt install build-essential libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
  ```

- **Arch Linux:**

  ```bash
  sudo pacman -S base-devel alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
  ```

- **Fedora:**

  ```bash
  sudo dnf install gcc make alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel
  ```

### 2. Compilação e execução

```bash
make          # compila o projeto (use `make clean` para limpar os arquivos de build)
./tetris      # execute a partir da raiz do projeto para carregar os arquivos de resources/
```

## Persistência de dados

A persistência é implementada integralmente em C no arquivo `src/game.c` (`game_save`, `game_load` e `game_delete_save`), utilizando leitura e escrita binária da biblioteca padrão (`fopen`, `fwrite`, `fread` e `remove`) no arquivo `save.dat`:

- **Salvamento:** ao fechar a janela durante uma partida em andamento (`STATE_PLAYING`), toda a estrutura `Game` (matriz do tabuleiro, peça atual, pontuação, tempo decorrido e temporizadores) é serializada diretamente em `save.dat`.
- **Carregamento:** ao iniciar o executável, o jogo tenta carregar `save.dat`; se o arquivo existir e for lido com sucesso, a partida é retomada exatamente de onde parou; caso contrário, um novo jogo é iniciado.
- **Remoção:** quando ocorre *Game Over*, o arquivo `save.dat` é removido automaticamente para que a próxima execução comece uma nova partida.

Como todo o projeto é escrito exclusivamente em C, não há integração com outras linguagens.

## Vídeo de apresentação

- [Assista ao vídeo de apresentação do projeto](<link do video>)

## Integrantes

- Amanda de Bastos Chagas
- Isadora Aires Franca
- João Victor Pinheiro Reis
- Miguel Qualhato Dias Rocha
