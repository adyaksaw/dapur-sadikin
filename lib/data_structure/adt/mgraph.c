#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"

/*Driver untuk graph.c */
int main () {
  Graph G;
  adrNode Pn1,Pn2;
  Point Trans12 = MakePoint(1,1);
  Point Spawn12 = MakePoint(1,2);
  Point Trans21 = MakePoint(2,1);
  Point Spawn21 = MakePoint(2,2);
  Matrix M1,M2;
  MakeEmpty_Map(2,2,&M1,1);
  MakeEmpty_Map(2,2,&M2,2);
  InsertNode_Graph(&G,&M1,&Pn1);
  InsertNode_Graph(&G,&M2,&Pn2);
  InsertEdge(&G,&M1,&M2,Trans12,Spawn12,RIGHT);
  InsertEdge(&G,&M2,&M1,Trans21,Spawn21,LEFT);
  printf("%d",Pn1);
  printf("%d",Pn2);

  return 0;
}
