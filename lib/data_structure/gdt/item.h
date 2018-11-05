/* File : item.h */

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "../data_type.h"

typedef struct{
  SmallNum id;
  string name;
} Item;

#define ItemID(I)   (I).id
#define ItemName(I) (I).name

#endif
