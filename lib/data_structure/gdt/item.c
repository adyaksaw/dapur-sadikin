#include <stdlib.h>
#include <stdio.h>

#include "item.h"

void PrintItem(Item item){
  printKata(item.name);
  printf(" ItemID: %d", ItemID(item));
}

boolean IsOrdered(Customer C, Item I){
	return (FoodOrderID(C) == ItemID(I));
}