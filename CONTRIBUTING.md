# Instruções para Contribuir

## Formatação e Autocomplete

Use a extensão "clangd" no VSCode (desative todas as outras extensões para a linguagem C) e habilite "Format on Save" nas configurações do VSCode.

Para que o autocomplete funcione: instale o `bear` com o gerenciador de pacotes da sua distribuição e rode o comando `make compdb`, o que vai gerar o arquivo `compile_commands.json`.

## Padrão de Nomenclatura

Escreva nomes de arquivos, funções, variáveis e tipos em inglês:

- Funções e variáveis em `snake_case` ([veja aqui](https://developer.mozilla.org/en-US/docs/Glossary/Snake_case)).
- `struct` e `enum` em `PascalCase` (ex.: `Game`, `PieceType`).
- Constantes e macros em `UPPER_SNAKE_CASE` (ex.: `DROP_INTERVAL`, `ROWS`).

Sempre que criar uma função em um arquivo `example.c`, inicie o nome dela com `example_` (ex.: `example_draw_rectangle`).

## Convenções de Código

- Declare funções usadas apenas dentro do próprio `.c` como `static`.
- Declare variáveis de controle de laços `for` fora do laço (ex.: `int r, c;`).
- Antes de enviar alterações, rode `make` e garanta que compila sem warnings (o `Makefile` usa `-Werror`).
