#include <unistd.h>  // para usleep
#include <stdlib.h> 
#include <time.h> // para randomizar as frutas


// aqui vamos incluir as possibilidades de exec em macos/linux e windows, ncurses ou pdcurses
#if defined(_WIN32) || defined(_WIN64)
    #include <curses.h>   
    #include <windows.h>  // sleep()
#else
    #include <ncurses.h>  
    #include <unistd.h>   // usleep()
#endif

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

void endgame(int pont) {
    bkgd(COLOR_PAIR(3)); 
    nodelay(stdscr, FALSE);
    clear();
    attron(COLOR_PAIR(4));
    mvprintw(LINES/2, (COLS - 9) / 2, "GAME OVER");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(5));
    mvprintw(LINES/2 + 1, (COLS - 13) / 2, "Pontuacao: %d", pont);
    attroff(COLOR_PAIR(5));
    attron(COLOR_PAIR(6));
    mvprintw(LINES/2 + 2, (COLS - 17) / 2, "ENTER - reiniciar");
    mvprintw(LINES/2 + 3, (COLS - 19) / 2, "ESC - fechar o jogo");
    attroff(COLOR_PAIR(6));
    refresh();
    int ch;
    while (1) {
        ch = getch();
        if (ch == '\n' || ch == KEY_ENTER) {
            clear();
            refresh();
            return; // reiniciar o jogo
        }
        if (ch == 27) { // esc
            endwin();   // fecha ncurses
            exit(0);    // finaliza o programa
        }
    }
}

int main() {
    
    int snake_x[100];
    int snake_y[100];
    int length;
    int dir;
    int ch;
    int fruit_x;
    int fruit_y;
    int paused = 0;
    srand(time(0));

    initscr();              // start no ncurses
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // cobra
    init_pair(2, COLOR_RED, COLOR_BLACK); // fruta
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // fundo preto
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK); // título game over
    init_pair(5, COLOR_YELLOW, COLOR_BLACK); // score
    init_pair(6, COLOR_CYAN, COLOR_BLACK); // instruções

    bkgd(COLOR_PAIR(3)); 
    noecho();               // nao imprimir teclas no terminal
    curs_set(FALSE);        // deixa o cursos invisivel
    keypad(stdscr, TRUE);   // aceita as teclas (nao ta funcionando sem isso)
    nodelay(stdscr, FALSE); // input block

    clear();
    attron(COLOR_PAIR(4));
    mvprintw(LINES/2 - 1, (COLS - 16) / 2, "JOGO DA COBRINHA");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(6));
    mvprintw(LINES/2, (COLS - 28) / 2, "Pressione ENTER para comecar");
    attroff(COLOR_PAIR(6));
    refresh();

    while ((ch = getch()) != '\n' && ch != KEY_ENTER) {
    }

    nodelay(stdscr, TRUE);  // input não bloqueante para o jogo

    length = 3;
    snake_x[0] = 10;
    snake_y[0] = 10;
    snake_x[1] = 9;
    snake_y[1] = 10;
    snake_x[2] = 8;
    snake_y[2] = 10;
    dir = RIGHT;

    fruit_x = rand() % (COLS / 2);
    fruit_y = rand() % LINES;

    while (1) {
        ch = getch();

        // pausa/despausa ESC (27)
        if (ch == 27) {
            paused = !paused;
            if (paused) {
                nodelay(stdscr, FALSE); // input fica bloqueado durante pause, vai que o usuario faz besteira
                clear();
                mvprintw(LINES/2 - 1, (COLS - 7) / 2, "PAUSADO");
                mvprintw(LINES/2, (COLS - 13) / 2, "Pontuacao: %d", length - 3);
                mvprintw(LINES/2 + 1, (COLS - 38) / 2, "Pressione ESC novamente para continuar");
                refresh();
            
                while ((ch = getch()) != 27) {
                }
                nodelay(stdscr, TRUE); // sem block
                continue; // restart loop
            }
        }

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

        // wrap-around CORRIGIDO
        if (snake_x[0] < 0) snake_x[0] = (COLS / 2) - 1;
        if (snake_x[0] >= (COLS / 2)) snake_x[0] = 0;
        if (snake_y[0] < 0) snake_y[0] = LINES - 1;
        if (snake_y[0] >= LINES) snake_y[0] = 0;

        if (snake_x[0] == fruit_x && snake_y[0] == fruit_y) {
            length++;
            fruit_x = rand() % (COLS / 2);
            fruit_y = rand() % LINES;
        }

        clear();

        // desenha a fruta primeiro 
        attron(COLOR_PAIR(2));
        mvprintw(fruit_y, fruit_x * 2, "@@");
        attroff(COLOR_PAIR(2));

        // depois a cobra
        for (int i = 0; i < length; i++) {
            attron(COLOR_PAIR(1));
            if (i == 0)
                mvprintw(snake_y[i], snake_x[i] * 2, "XX"); // cabeça
            else
                mvprintw(snake_y[i], snake_x[i] * 2, "OO"); // corpo
            attroff(COLOR_PAIR(1));
        }

        // morte por colisao
        for (int j = 1; j < length; j++) {
            if ((snake_x[j] == snake_x[0]) && (snake_y[j] == snake_y[0])) {
                endgame(length - 3);
                // quando voltar do game over, reinicia a cobra e fruta
                length = 3;
                snake_x[0] = 10;
                snake_y[0] = 10;
                snake_x[1] = 9;
                snake_y[1] = 10;
                snake_x[2] = 8;
                snake_y[2] = 10;
                dir = RIGHT;
                fruit_x = rand() % (COLS / 2);
                fruit_y = rand() % LINES;
                nodelay(stdscr, TRUE); // sem block
                break;
            }
        }

        mvprintw(0, 2, "Pontuacao: %d", length - 3);

        refresh();

        // delayzinho pq ta muito rapido
        
        #if defined(_WIN32) || defined(_WIN64)
            Sleep(100); // milissegundos no Windows
        #else
            usleep(100000); // microssegundos em Unix/Mac
        #endif
    }

    return 0;
}