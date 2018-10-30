/* File : obj-handler.h */
/* Dapur SADIKIN Game Object Handler */

#ifndef OBJ_HANDLER_H
#define OBJ_HANDLER_H

#include "obj-def.h"
#include "map-handler.h"

#define PLAYER_SAVE_DIR "~dir/map.txt"

/* ********** PLAYER ********** */
void Load_Player (player * player, file * fplayer);
void Move_Player (Matrix * M, player * player, Point P0, Point P1);

#endif
