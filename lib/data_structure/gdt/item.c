#include <stdlib.h>
#include <stdio.h>

#include "item.h"

void PrintItem(Item item){
  printKata(item.name);
  printf(" ItemID: %d", ItemID(item));
}