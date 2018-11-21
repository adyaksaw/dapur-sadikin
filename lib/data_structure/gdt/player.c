#include <stdio.h>
#include <stdlib.h>

#include "player.h"

void Load_Player (Player * player, FILE * player_save_file){

}

void Move_Player_Direction (Matrix * M, Player * player, Direction dir){
    Point newPoint;
    if (dir == UP){
        Ordinat(newPoint) = Ordinat((*player).pos) + 1;
        Move_Player(M, player, (*player).pos, newPoint);
    }
}

void Move_Player (Matrix * M, Player * player, Point P0, Point P1){
    if (isPointValid(P1) && ElmtMx(*M, (int) Absis(P1), (int) Ordinat(P1)).tag == EMPTY){
        SetElement_Matrix(M, (int) Absis(P1), (int) Ordinat(P1), PlayerObject());
        (*player).pos = P1;
    }
}

boolean isPointValid(Point P){
    return Absis(P) >= 1 && Absis(P) <= 8 && Ordinat(P) >= 1 && Ordinat(P) <= 8;
}

void Print_Player(Player player){
    printf("Nama : ");
    printKata(player.name);
    printf("\n");
    printf("Uang : %f\n", player.money);
    printf("Nyawa : %d\n", player.life);
}

void Set_Player_Name(Player * player, char nama[], int length){
    isiKata(&((*player).name), nama, length);
}

void Create_New_Player(Player * player){
    isiKata(&((*player).name), "", 0);
    Money(*player) = 0;
    Life(*player) = 3;
    MakeEmpty_Table(&(Hand(*player)));
    CreateEmpty_Stack(&(Food(*player)));
}