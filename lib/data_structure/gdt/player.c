#include <stdio.h>
#include <stdlib.h>

#include "player.h"

void Load_Player (Player * player, FILE * player_save_file){

}

void Move_Player_Direction (Matrix * M, Player * player, Direction dir){
    printf("TRYING TO MOVE\n");

    Point newPoint;
    newPoint = (*player).pos;
    
    if (dir == UP){
        printf("TRYING TO MOVE2\n");
        Absis(newPoint) += -1;
        Move_Player(M, player, newPoint);
    }else if (dir == DOWN){
        printf("TRYING TO MOVE2\n");
        Absis(newPoint) += 1;
        Move_Player(M, player, newPoint);
    }else if (dir == RIGHT){
        printf("TRYING TO MOVE2\n");
        Ordinat(newPoint) += 1;
        Move_Player(M, player, newPoint);
    }else {
        printf("TRYING TO MOVE2\n");
        Ordinat(newPoint) += -1;
        Move_Player(M, player, newPoint);
    }
}

boolean isPointValid(Point P){
    printf("CHECKING (%.0f, %f.0f).\n", Absis(P), Ordinat(P));
    return Absis(P) >= 1 && Absis(P) <= 8 && Ordinat(P) >= 1 && Ordinat(P) <= 8;
}

void Move_Player (Matrix * M, Player * player, Point P){
    printf("IsPointValid: %d\n", isPointValid(P));
    if (isPointValid(P) && ElmtMx(*M, (int) Absis(P), (int) Ordinat(P)).tag == EMPTY){
        Object EmptyObject;
        EmptyObject.tag = EMPTY;
        SetTag_Matrix(M, (int) Absis((*player).pos), (int) Ordinat((*player).pos), EMPTY);
        printf("MOVING\n");
        SetTag_Matrix(M, (int) Absis(P), (int) Ordinat(P), PLAYER_POS);
        (*player).pos = P;
    }
}

void Print_Player(Player player){
    printf("Nama : ");
    printKata(player.name);
    printf("\n");
    printf("Uang : %d\n", player.money);
    printf("Nyawa : %d\n", player.life);
    printf("Posisi Baris %.1f Kolom %.1f.\n", Ordinat(player.pos), Ordinat(player.pos));
}

void Set_Player_Name(Player * player, char nama[], int length){
    isiKata(&((*player).name), nama, length);
}

void Create_New_Player(Player * player){
    isiKata(&((*player).name), "", 0);
    Money(*player) = 0;
    Life(*player) = 3;
    CreateEmpty_Stack(&(Hand(*player)));
    CreateEmpty_Stack(&(Food(*player)));
}

Object * Closest_Empty_Table(Player player, Matrix *M){
  int player_i = (int) Absis(player.pos);
  int player_j = (int) Ordinat(player.pos);

  int counter = 0;

  int i = -1;
  int j = -1;

  Object * retVal = NULL;

  while (retVal == NULL && counter < 9){
    Point nP;
    Absis(nP) = player_i + i;
    Ordinat(nP) = player_j + j;
    if (isPointValid(nP)){
      if (ElmtMx(*M, (int) Absis(nP), (int) Ordinat(nP)).tag == TABLE){
        if (!ElmtMx(*M, (int) Absis(nP), (int) Ordinat(nP)).data.table.isOccupied){
          retVal = &(ElmtMx(*M, (int) Absis(nP), (int) Ordinat(nP)));
        }
      }
    }
    if (j < 1){
      j++;
    }else {
      j = -1;
      i++;
    }
    counter++;
  }
  //printf("Memaddress: %p\n", retVal);
  return retVal;
}

Object * Closest_Table(Player player, Matrix *M){
  int player_i = (int) Absis(player.pos);
  int player_j = (int) Ordinat(player.pos);

  int counter = 0;

  int i = -1;
  int j = -1;

  Object * retVal = NULL;

  while (retVal == NULL && counter < 9){
    Point nP;
    Absis(nP) = player_i + i;
    Ordinat(nP) = player_j + j;
    if (isPointValid(nP)){
      if (ElmtMx(*M, (int) Absis(nP), (int) Ordinat(nP)).tag == TABLE){
        retVal = &(ElmtMx(*M, (int) Absis(nP), (int) Ordinat(nP)));
      }
    }
    if (j < 1){
      j++;
    }else {
      j = -1;
      i++;
    }
    counter++;
  }
  //printf("Memaddress: %p\n", retVal);
  return retVal;
}

Object * Closest_Object(Player player, Matrix *M, GameObj Obj){
  int player_i = (int) Absis(player.pos);
  int player_j = (int) Ordinat(player.pos);

  int counter = 0;

  int nextI[4] = {0,1,0,-1};
  int nextJ[4] = {1,0,-1,0};

  Object * retVal = NULL;

  while (retVal == NULL && counter < 9){
    Point nP;
    Absis(nP) = player_i + nextI[counter];
    Ordinat(nP) = player_j + nextJ[counter];
    if (isPointValid(nP)){
      if (ElmtMx(*M, (int) Absis(nP), (int) Ordinat(nP)).tag == Obj){
        retVal = &(ElmtMx(*M, (int) Absis(nP), (int) Ordinat(nP)));
      }
    }
    counter++;
  }
  //printf("Memaddress: %p\n", retVal);
  return retVal;
}

void Reduce_Life(Player *player){
  if(Life(*player) > 0)Life(*player)--;
}

void Masak(Player * player, BinTree resep){
    if (!IsEmpty_Stack((*player).hand)){
        Node *currentNode = NULL;
        currentNode = resep;
        if (currentNode != NULL){
            boolean inventoriValid = true;
            Stack reversedStack = Reverse_Stack(&((*player).hand));
            SmallNum currentStackElmt = Top(reversedStack);

            if (SearchItemTree(resep, reversedStack.T[currentStackElmt].id).id != 255){
                printf("ADA\n");
            }

            while (inventoriValid && currentStackElmt > 0){
                printf("Current stack elmt %d\n", currentStackElmt);
                printf("Membandingkan hand %d dengan pohon %d\n", reversedStack.T[currentStackElmt].id, Akar(currentNode).id);
                if (reversedStack.T[currentStackElmt].id != Akar(currentNode).id){
                    printf("Adalah tidak sama hand %d dengan pohon %d\n", reversedStack.T[currentStackElmt].id, Akar(currentNode).id);
                    inventoriValid = false;
                }else {
                    printf("Adalah sama hand %d dengan pohon %d\n", reversedStack.T[currentStackElmt].id, Akar(currentNode).id);
                    currentStackElmt -= 1;
                    printf("Current stack elmt %d\n", currentStackElmt);
                    if (currentStackElmt > 0){
                        if (SearchItemTree(Left(currentNode), reversedStack.T[currentStackElmt].id).id != 255){
                            currentNode = Left(currentNode);
                        }else if (SearchItemTree(Right(currentNode), reversedStack.T[currentStackElmt].id).id != 255){
                            currentNode = Right(currentNode);
                        }else {
                            inventoriValid = false;
                        }
                    }
                }
            }

            currentNode = Left(currentNode);
            if (inventoriValid){
                inventoriValid = IsTreeOneElmt(currentNode);
            }

            if (inventoriValid){
                printf("Akan dimasak ");
                printKata(Info(currentNode).name);
                printf("\n");
                Push_Stack(&((*player).food), Info(currentNode));
                CreateEmpty_Stack(&((*player).hand));
            }else {
                printf("Tidak ada resep yang sesuai!\n");
            }
        }
    }else{
        printf("Tangan anda kosong!\n");
    }
}
