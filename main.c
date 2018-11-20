#include <stdio.h>
#include <stdlib.h>

#include "lib/data_structure/data_type.h"
#include "lib/data_structure/gdt/game_data_type.h"
#include "lib/handler/handler_include.h"

GameState gameState;

int main(){
    gameState = MAIN_MENU;

    Kata inputCommand;
    isiKata(&inputCommand, "", 0);

    Kata quitCommand;
    isiKata(&quitCommand, "quit", 4);

    printf("%d\n", gameState);

    while (!IsKataSama(inputCommand, quitCommand)){
        printf("WELKAM!\n");
        char rawInput[50];
        scanf("%s", &rawInput);
        isiKata(&inputCommand, rawInput, 4);
        printKata(inputCommand);
        printf("\n");
    }

    gameState = CREDITS;
    printf("%d\n", gameState);
}