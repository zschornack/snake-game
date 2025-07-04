# Jogo da Cobrinha (Snake) em C com Ncurses

*Um jogo clássico da cobrinha feito em C, usando ncurses (ou pdcurses) para rodar no terminal. Inclui cores, detecção de colisão, pausa e placar. Suporta Linux, macOS e Windows.*

## Requisitos

### Linux/macOS
- Compilador C (gcc ou clang)
- Biblioteca ncurses
  
*Instalação ncurses Ubuntu/Debian:*
  ***sudo apt install libncurses5-dev***
*Instalação ncurses MacOS*
***brew install ncurses***

### Windows
- Compilador MinGW ou MSVC
- Biblioteca PDCurses


## Como compilar

**Linux/macOS**
  *gcc -o snake main.c -lncurses*
  
**Windows (MinGW)**
  *gcc -o snake.exe snake.c -lpdcurses*

⚠️ Certifique-se de ter a biblioteca PDCurses instalada ou os arquivos .h e .a disponíveis.


## Como jogar

Inicie o jogo rodando o binário:
**Linux/macOS:**
  *./snake*
  
**Windows:**
  *snake.exe*

***Use as setas do teclado para mover a cobrinha:***
↑ para cima
↓ para baixo
← para esquerda
→ para direita
Pressione ESC para pausar ou sair:
ESC pausa o jogo (pressione novamente para retomar)
Na tela de Game Over:
ENTER reinicia
ESC sai


## Compatibilidade

Linux e macOS (usando ncurses)
Windows (usando PDCurses)
O código detecta automaticamente o sistema para incluir a biblioteca correta.

## Observações

A tela usa wrap-around nas bordas (a cobra aparece do outro lado)
A velocidade do jogo pode ser ajustada editando o delay (usleep/Sleep) no código
