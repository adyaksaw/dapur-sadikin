#include <stdio.h>
#include <stdlib.h>

#include "lib/data_structure/data_type.h"
#include "lib/data_structure/gdt/game_data_type.h"
#include "lib/handler/handler_include.h"

#define initialX 4
#define initialY 4


GameState gameState;
Player player;

Matrix Map1, Map2, Map3, Kitchen;

void Init(){
    Create_New_Player(&player);
    LoadMap(&Map1, &Map2, &Map3, &Kitchen);
    SetElement_Matrix(&Map1, initialX, initialY, PlayerObject());
}

void MainScreen(){
    printf("Main Screen\n");
    char rawInput[10] = "";
    while (gameState == MAIN_MENU){
        Create_New_Player(&player);
        printf("Welcome to Dapur Sadikin!\n");
        printf("What is your name?\n");
        printf("Name : ");
        scanf("%s", &rawInput);
        Set_Player_Name(&player, rawInput, 10);
        printf("Selamat datang, ");
        printKata(player.name);
        printf(".\n");
        gameState = IN_GAME;
    }
}

void MainGame(){
    printf("Main Game\n");
    char rawInput[10] = "";
    Kata processedInput;
    Kata quitInput;
    Kata statusInput;
    isiKata(&quitInput, "quit", 4);
    isiKata(&statusInput, "status", 6);
    Queue CustomerQueue;
    CreateEmpty_Queue(&CustomerQueue, 5);
    Customer *newCustomer;
    while (gameState == IN_GAME){
        if (IsKataSama(processedInput, quitInput)){
            gameState = CREDITS;
        }else if (IsKataSama(processedInput, statusInput)){
            Print_Player(player);
        }else {
            if (!IsFull_Queue(CustomerQueue)){
                newCustomer = GenerateCustomer();
                printCustomer(*newCustomer);
                Add_Queue(&CustomerQueue, newCustomer);
                printf("In Top Queue: ");
                printCustomer(*(InfoHead(CustomerQueue)));
            }
            Print_Room(Map1);
            printf("Input : ");
            scanf("%s", &rawInput);
            isiKata(&processedInput, rawInput, 10);
        }
    }
    DeAlokasi_Queue(&CustomerQueue);
}

int main(){
    Init();

    gameState = MAIN_MENU;
    printf("%d\n", gameState);

    MainScreen();

    MainGame();

    gameState = CREDITS;
    printf("%d\n", gameState);
}