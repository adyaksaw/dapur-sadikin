#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

#include "../data_type.h"

#include "../adt/abstract_data_type.h"

#include "../adt/matrix.h"
#include "../adt/table.h"
#include "../adt/stack.h"
#include "../adt/tree.h"
#include "map.h"



typedef struct {
  Kata name;
  Point pos;
  long money;
  SmallNum life;
  Stack hand;          // refer to 'data_structure/arraystr.h'
  Stack food;           // refer to 'data_structure/stackt.h'
  Matrix * currentMap;
  int currentRoom;
} Player;

/* *** Player *** */
#define Name(P)   (P).name
#define Money(P)  (P).money
#define Life(P)   (P).life
#define Hand(P)   (P).hand
#define Food(P)   (P).food

void Print_Player(Player player);

void Create_New_Player(Player * player);

void Set_Player_Name(Player * player, char nama[], int length);

void Load_Player (Player * player, FILE * player_save_file);

void Move_Player_Direction (Matrix * M, Player * player, Direction dir);

boolean isPointValid(Point P);

void Move_Player (Matrix * M, Player * player, Point P);

Object * Closest_Table(Player player, Matrix *M);

Object * Closest_Empty_Table(Player player, Matrix *M);

void Reduce_Life(Player *player);

Object * Closest_Object(Player player, Matrix *M, GameObj Obj);

void Masak(Player * player, BinTree resep);

#endif
