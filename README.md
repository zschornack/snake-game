#Jogo da Cobrinha (Snake) em C com Ncurses#

Um jogo clássico da cobrinha feito em C, usando ncurses (ou pdcurses) para rodar no terminal.
Inclui cores, detecção de colisão, pausa e placar. Suporta Linux, macOS e Windows.

##Descrição##

Este é um clone simples do jogo Snake, com as seguintes características:

Cobra que cresce ao comer frutas
Pontuação exibida na tela
Pausa/retomada com a tecla ESC
Detecção de colisão com o próprio corpo
Tela "Game Over" com opção de reiniciar ou sair
⚙️ Requisitos

Linux/macOS
Compilador C (gcc ou clang)
Biblioteca ncurses
Para instalar no Ubuntu/Debian:

sudo apt install libncurses5-dev
No macOS (via Homebrew):

brew install ncurses
Windows
Compilador MinGW ou MSVC
Biblioteca PDCurses
🛠️ Como compilar

Linux/macOS
gcc -o snake snake.c -lncurses
Windows (MinGW)
gcc -o snake.exe snake.c -lpdcurses
⚠️ Certifique-se de ter a biblioteca PDCurses instalada ou os arquivos .h e .a disponíveis.

🎮 Como jogar

Inicie o jogo rodando o binário:
Linux/macOS:

./snake
Windows:

snake.exe
Use as setas do teclado para mover a cobrinha:
↑ para cima
↓ para baixo
← para esquerda
→ para direita
Pressione ESC para pausar ou sair:
ESC pausa o jogo (pressione novamente para retomar)
Na tela de Game Over:
ENTER reinicia
ESC sai
🖥️ Compatibilidade

Linux e macOS (usando ncurses)
Windows (usando PDCurses)
O código detecta automaticamente o sistema para incluir a biblioteca correta.

📌 Observações

A tela usa wrap-around nas bordas (a cobra aparece do outro lado)
A velocidade do jogo pode ser ajustada editando o delay (usleep/Sleep) no código
