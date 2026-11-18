# Instruções para Contribuir

## Formatação e Autocomplete

Use a extensão "clangd" no VSCode (desative todas as outras extensões para a linguagem C) e habilite "Format on Save" nas configurações do VSCode.

Para que o autocomplete funcione: instale o `bear` com o gerenciador de pacotes da sua distribuição e rode o comando `make compdb`, o que vai gerar o arquivo `compile_commands.json`.

## Padrão de Nomenclatura

Use o snake case ([veja aqui](https://developer.mozilla.org/en-US/docs/Glossary/Snake_case)).

Sempre que criar uma função em um arquivo `exemplo.c`, inicie o nome dela com `exemplo_` (ex.: `exemplo_desenha_retangulo`).
