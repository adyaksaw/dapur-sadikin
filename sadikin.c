#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/handler/core/session.h"
#include <ncurses.h>

int main()
{
    initscr();            /* Start curses mode 		*/
    raw();                /* Line buffering disabled	*/
    keypad(stdscr, TRUE); /* We get F1, F2 etc..		*/
    noecho();             /* Don't echo() while we do getch */

    Init();
    printw("After init\n");
    //PrintAllMemory(Map1);
    printw("After init2\n");
    //PrintAllMemory(Map1);

    gameState = MAIN_MENU;
    printw("%d\n", gameState);

    MainScreen();
    printw("Player pos : %f %f", Absis(player.pos), Ordinat(player.pos));
    printw("After mainscreen\n");
    //PrintAllMemory(Map1);
    printw("After mainscreen2\n");
    printw("Player pos : %f %f", Absis(player.pos), Ordinat(player.pos));
    //PrintAllMemory(Map1);

    MainGame();

    gameState = CREDITS;
    printw("%d\n", gameState);

    printw("Before quit\n");
    //PrintAllMemory(Map1);
    printw("Before quit2\n");
    //PrintAllMemory(Map1);

    endwin(); /* End curses mode		  */

    return 0;
}