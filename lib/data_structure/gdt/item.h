/* File : item.h */

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "../adt/mesinbaca.h"

#include "../data_type.h"

typedef struct{ 
  SmallNum id;
  Kata name;
} Item;

#define ItemID(I)   (I).id
#define ItemName(I) (I).name.TabKata

void PrintItem(Item item);

#endif
