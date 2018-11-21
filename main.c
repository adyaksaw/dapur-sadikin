#include <stdio.h>
#include <stdlib.h>

#include "lib/data_structure/data_type.h"
#include "lib/data_structure/gdt/game_data_type.h"
#include "lib/handler/handler_include.h"

#define initialX 4
#define initialY 4


GameState gameState;
Player player;
Queue CustomerQueue;

Object *ArrayOfMeja[13];

Matrix Map1, Map2, Map3, Kitchen;

void PrintAllOrder(){
    for (int i = 1; i <= 12; i++){
        if (IsOccupied(*(ArrayOfMeja[i]))){
            printf("Meja No.%d memesan OrderID %d.\n", i, OrdersAt(*(ArrayOfMeja[i])));
        }else {
            printf("Meja No.%d kosong.\n", i);
        }
    }
}

void Init(){
    Create_New_Player(&player);
    LoadMap(&Map1, &Map2, &Map3, &Kitchen);

    /*
        Melakukan inisialisasi dari array of pointer ArrayOfMeja.
        ArrayOfMeja akan berisi pointer menuju semua objek meja sesuai nomornya.
        Sebagai contoh, ketika diakses *(ArrayOfMeja[3]) maka akan diakses
        memori yang menyimpan objek yang merupakan meja dengan nomor meja 3.
    */
    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                printf("Init Meja Nomor %d.\n", ElmtMx(Map1, i, j).data.table.num);
                ArrayOfMeja[ElmtMx(Map1, i, j).data.table.num] = &(ElmtMx(Map1, i, j));
            }
        }
    }

    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                printf("Init Meja Nomor %d.\n", ElmtMx(Map2, i, j).data.table.num);
                ArrayOfMeja[ElmtMx(Map2, i, j).data.table.num] = &(ElmtMx(Map2, i, j));
            }
        }
    }

    for (int i = 1; i <= 8; i++){
        for (int j = 1; j <= 8; j++){
            if (ElmtMx(Map1, i, j).tag == TABLE){
                printf("Init Meja Nomor %d.\n", ElmtMx(Map3, i, j).data.table.num);
                ArrayOfMeja[ElmtMx(Map3, i, j).data.table.num] = &(ElmtMx(Map3, i, j));
            }
        }
    }

    player.currentMap = &Map1;

    Absis(player.pos) = initialX;
    Ordinat(player.pos) = initialY;

    SetElement_Matrix(player.currentMap, initialX, initialY, PlayerObject());
}

void CustomerGenerator(){
    if (!IsFull_Queue(CustomerQueue)){
        Customer *newCustomer;
        newCustomer = GenerateCustomer();

        printf("New Customer\n");
        printCustomer(*newCustomer);

        Add_Queue(&CustomerQueue, newCustomer);
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

    Kata queueInput;
    isiKata(&queueInput, "queue", 5);

    Kata allOrderInput;
    isiKata(&allOrderInput, "allOrder", 8);

    Kata placeInput;
    isiKata(&placeInput, "place", 5);

    if (IsKataSama(processedInput, quitInput)){
        gameState = CREDITS;
    }else if (IsKataSama(processedInput, statusInput)){
        Print_Player(player);
    }else if (IsKataSama(processedInput, moveInputUp)){
        Move_Player_Direction(player.currentMap, &player, UP);
    }else if (IsKataSama(processedInput, moveInputDown)){
        Move_Player_Direction(player.currentMap, &player, DOWN);
    }else if (IsKataSama(processedInput, moveInputLeft)){
        Move_Player_Direction(player.currentMap, &player, LEFT);
    }else if (IsKataSama(processedInput, moveInputRight)){
        Move_Player_Direction(player.currentMap, &player, RIGHT);
    }else if (IsKataSama(processedInput, queueInput)){
        Print_Queue(CustomerQueue);
    }else if (IsKataSama(processedInput, allOrderInput)){
        PrintAllOrder();
    }else if (IsKataSama(processedInput, placeInput)){
        Object * ClosestTable = Closest_Empty_Table(player, *(player.currentMap));
        if (ClosestTable != NULL){
            printf("Meja dengan nomor %d kosong.\n", (*ClosestTable).data.table.num);
        }else {
            printf("Tidak ada meja kosong disekitarmu!\n");
        }
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

    CreateEmpty_Queue(&CustomerQueue, 5);

    while (gameState == IN_GAME){
        printf("Map 1\n");
        Print_Room(Map1);
        printf("Map 2\n");
        Print_Room(Map2);
        printf("Map 3\n");
        Print_Room(Map3);
        printf("Dapur\n");
        Print_Kitchen(Kitchen);
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