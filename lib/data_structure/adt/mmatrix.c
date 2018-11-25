#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"

int main () {
  Matrix M1;
  MakeEmpty_Map(2,2,&M1,1);
  SetTag_Matrix(&M1, 1, 1, STOVE);
  SetTag_Matrix(&M1, 1, 2, STOVE);
  SetTag_Matrix(&M1, 2, 1, STOVE);
  SetTag_Matrix(&M1, 2, 2, STOVE);
  Print_Room(M1);

  return 0;
}
