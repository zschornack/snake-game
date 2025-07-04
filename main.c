#include <ncurses.h>
#include <unistd.h>  // para usleep
#include <stdlib.h> 
#include <time.h> // para randomizar as frutas

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

void endgame(int pont) {
    nodelay(stdscr, FALSE);   // Torna getch() bloqueante para esperar input
    clear();                   
    mvprintw(LINES/2, (COLS - 9) / 2, "GAME OVER");
    mvprintw(LINES/2 + 1, (COLS - 14) / 2, "Score: %d", pont);   
    mvprintw(LINES/2 + 2, (COLS - 28) / 2, "Pressione qualquer tecla para sair");
    refresh();
    getch();                   // espera o jogador apertar algo
    endwin();                  // fecha ncurses
    exit(0);                   // finaliza o programa
}

int main() {
    
    int snake_x[100];
    int snake_y[100];
    int length;
    int dir;
    int ch;
    int fruit_x;
    int fruit_y;
    srand(time(0));

    initscr();              // Inicializa ncurses
    noecho();               // Não imprime teclas
    curs_set(FALSE);        // Esconde cursor
    keypad(stdscr, TRUE);   // Aceita teclas especiais
    nodelay(stdscr, TRUE);  // Input não bloqueante

    length = 3;
    snake_x[0] = 10;
    snake_y[0] = 10;
    snake_x[1] = 9;
    snake_y[1] = 10;
    snake_x[2] = 8;
    snake_y[2] = 10;
    dir = RIGHT;

    fruit_x = rand() % COLS;
    fruit_y = rand() % LINES;
    mvprintw(fruit_y, fruit_x, "@");                            

    while (1) {
          
        ch = getch();
        // leitura de input + impedir bug 180 graus
        if (ch == KEY_UP && dir != DOWN) dir = UP;
        else if (ch == KEY_DOWN && dir != UP) dir = DOWN;
        else if (ch == KEY_LEFT && dir != RIGHT) dir = LEFT;
        else if (ch == KEY_RIGHT && dir != LEFT) dir = RIGHT;

        // update da cobra (shift corpo)
        for (int i = length - 1; i > 0; i--) {
            snake_x[i] = snake_x[i-1];
            snake_y[i] = snake_y[i-1];
        }

        // mover a cabeça
        switch (dir) {
            case UP:    snake_y[0]--; break;
            case DOWN:  snake_y[0]++; break;
            case LEFT:  snake_x[0]--; break;
            case RIGHT: snake_x[0]++; break;
        }

        // wrap-around
        if (snake_x[0] < 0) snake_x[0] = COLS - 1;
        if (snake_x[0] >= COLS) snake_x[0] = 0;
        if (snake_y[0] < 0) snake_y[0] = LINES - 1;
        if (snake_y[0] >= LINES) snake_y[0] = 0;

        if (snake_x[0] == fruit_x && snake_y[0] == fruit_y) {
            length++;
            fruit_x = rand() % COLS;
            fruit_y = rand() % LINES;
        }

        clear();

        // desenha a fruta primeiro 
        mvprintw(fruit_y, fruit_x, "@");

        // depois a cobra
        for (int i = 0; i < length; i++) {
            if (i == 0) {
                mvprintw(snake_y[i], snake_x[i], "X");  // cabeça
            } else {
                mvprintw(snake_y[i], snake_x[i], "O");  // corpo
            }
        }

        // morte por colisao
        for (int j = 1; j < length; j++) {
            if ((snake_x[j] == snake_x[0]) && (snake_y[j] == snake_y[0])) {
                endgame(length - 3);
                break;
            }
        }

        refresh();

        // delayzinho pq ta muito rapido
        usleep(100000);
    }

    return 0;
}


