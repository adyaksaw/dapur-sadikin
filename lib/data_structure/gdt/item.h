/* File : item.h */

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "../data_type.h"

#define ItemID(I)   (I).id
#define ItemName(I) (I).name

typedef struct{
    SmallNum id;
    string name;
} Item;

#endif