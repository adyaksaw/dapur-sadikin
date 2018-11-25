#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/handler/core/session.h"
#include <ncurses.h>

int main()
{
    Init();
    printf("After init\n");
    //PrintAllMemory(Map1);
    printf("After init2\n");
    //PrintAllMemory(Map1);

    gameState = MAIN_MENU;
    printf("%d\n", gameState);

    MainScreen();
    printf("Player pos : %f %f", Absis(player.pos), Ordinat(player.pos));
    printf("After mainscreen\n");
    //PrintAllMemory(Map1);
    printf("After mainscreen2\n");
    printf("Player pos : %f %f", Absis(player.pos), Ordinat(player.pos));
    //PrintAllMemory(Map1);

    MainGame();

    gameState = CREDITS;
    printf("%d\n", gameState);

    printf("Before quit\n");
    //PrintAllMemory(Map1);
    printf("Before quit2\n");
    //PrintAllMemory(Map1);

    return 0;
}