#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>

#include "../data_type.h"

#include "../adt/matrix.h"
#include "../adt/table.h"
#include "../adt/stack.h"

/* *** Player *** */
#define Name(P)   (P).name
#define Money(P)  (P).money
#define Life(P)   (P).life
#define Hand(P)   (P).hand
#define Food(P)   (P).food

typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
} Direction;

typedef struct {
  string name;            // refer to 'data_structure/string.h'
  Point pos;
  long money;
  SmallNum life;
  Table hand;          // refer to 'data_structure/arraystr.h'
  Stack food;           // refer to 'data_structure/stackt.h'
} Player;

void Load_Player (Player * player, file * player_save_file);

void Move_Player_Direction (Matrix * M, Player * player, Direction dir);

void Move_Player (Matrix * M, Player * player, Point P0, Point P1);

#endif