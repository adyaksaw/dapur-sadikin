#include "listrek.h"
#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"


int main () {
  int A,i;
  List L1,L2,L3,LTemp;
  L1 = Nil;
  L2 = Nil;
  L3 = Nil;
  LTemp = Nil;
  for (i = 1 ; i <= 10 ; ++i){
    scanf("%d",&A);
    L2 = KonsB_ListRek(LTemp,A);
    LTemp = L2;
  }
  printf("Berikut ini adalah isi dari List L2 (awal)\n");
  PrintList_ListRek(L2);

}
