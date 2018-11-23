/* File : item.h */

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "../adt/mesinbaca.h"

#include "../data_type.h"

#include "customer.h"

typedef struct{ 
  SmallNum id;
  Kata name;
} Item;

#define ItemID(I)   (I).id
#define ItemName(I) (I).name.TabKata
#define FoodPrice 15000
#define FoodPriceModifier 3

void PrintItem(Item item);

boolean IsOrdered(Customer C, Item I);

#endif
