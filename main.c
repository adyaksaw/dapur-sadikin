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

    Absis(player.pos) = initialX;
    Ordinat(player.pos) = initialY;

    SetElement_Matrix(&Map1, initialX, initialY, PlayerObject());
}

void CustomerGenerator(Queue * CustomerQueue){
    if (!IsFull_Queue(*CustomerQueue)){
        Customer *newCustomer;
        newCustomer = GenerateCustomer();

        printCustomer(*newCustomer);

        Add_Queue(CustomerQueue, newCustomer);

        printf("In Top Queue: ");
        printCustomer(*(InfoHead(*CustomerQueue)));
    }
}

void InputProcessor(char input[], int input_length){
    Kata processedInput;
    isiKata(&processedInput, input, input_length);
    
    Kata quitInput;
    isiKata(&quitInput, "quit", 4);

    Kata statusInput;
    isiKata(&statusInput, "status", 6);

    Kata moveInputUp;
    isiKata(&moveInputUp, "GU", 2);

    Kata moveInputDown;
    isiKata(&moveInputDown, "GD", 2);

    Kata moveInputLeft;
    isiKata(&moveInputLeft, "GL", 2);

    Kata moveInputRight;
    isiKata(&moveInputRight, "GR", 2);

    if (IsKataSama(processedInput, quitInput)){
        gameState = CREDITS;
    }else if (IsKataSama(processedInput, statusInput)){
        Print_Player(player);
    }else if (IsKataSama(processedInput, moveInputUp)){
        Move_Player_Direction(&Map1, &player, UP);
    }else if (IsKataSama(processedInput, moveInputDown)){
        Move_Player_Direction(&Map1, &player, DOWN);
    }else if (IsKataSama(processedInput, moveInputLeft)){
        Move_Player_Direction(&Map1, &player, LEFT);
    }else if (IsKataSama(processedInput, moveInputRight)){
        Move_Player_Direction(&Map1, &player, RIGHT);
    }
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

    Queue CustomerQueue;
    CreateEmpty_Queue(&CustomerQueue, 5);

    while (gameState == IN_GAME){
        Print_Room(Map1);
        printf("Input : ");
        scanf("%s", &rawInput);
        InputProcessor(rawInput, 10);
        CustomerGenerator(&CustomerQueue);
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