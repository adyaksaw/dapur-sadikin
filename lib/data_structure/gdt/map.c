#include "player.h"

void CreateBigMap (Matrix *M1, Matrix *M2 , Matrix *M3 , Matrix *M4, Graph *BIG_MAP) {
  Point Trans12, Spawn12, Trans14, Spawn14;
  Point Trans21, Spawn21, Trans23, Spawn23;
  Point Trans34, Spawn34, Trans32, Spawn32;
  Point Trans41, Spawn41, Trans43, Spawn43;
  adrNode Pn1,Pn2,Pn3,Pn4;

  Trans12 = MakePoint(5,8);
  Spawn12 = MakePoint(5,1);
  Trans14 = MakePoint(8,5);
  Spawn14 = MakePoint(1,5);

  Trans21 = MakePoint(5,1);
  Spawn21 = MakePoint(5,8);
  Trans23 = MakePoint(8,5);
  Spawn23 = MakePoint(1,5);

  Trans34 = MakePoint(5,1);
  Spawn34 = MakePoint(5,8);
  Trans32 = MakePoint(1,5);
  Spawn32 = MakePoint(8,5);

  Trans41 = MakePoint(1,5);
  Spawn41 = MakePoint(8,5);
  Trans43 = MakePoint(5,8);
  Spawn43 = MakePoint(5,1);

  //CreateGraph(M1,BIG_MAP);
  InsertNode_Graph(BIG_MAP,M1,&Pn1);
  printf("Pn1 = %d\n",Pn1);
  InsertNode_Graph(BIG_MAP,M2,&Pn2);
  printf("Pn2 = %d\n",Pn2);
  InsertNode_Graph(BIG_MAP,M3,&Pn3);
  printf("Pn3 = %d\n",Pn3);
  InsertNode_Graph(BIG_MAP,M4,&Pn4);
  printf("Pn4 = %d\n",Pn4);

  if (SearchNode_Graph(*BIG_MAP,M1) == Nil ){
    printf("Node M1 Nil\n");
  }

  if (SearchNode_Graph(*BIG_MAP,M2) == Nil ){
    printf("Node M2 Nil\n");
  }

  if (SearchNode_Graph(*BIG_MAP,M3) == Nil ){
    printf("Node M3 Nil\n");
  }

  if (SearchNode_Graph(*BIG_MAP,M4) == Nil ){
    printf("Node M4 Nil\n");
  }

  InsertEdge(BIG_MAP,M1,M2,Trans12,Spawn12,RIGHT);
  InsertEdge(BIG_MAP,M1,M4,Trans14,Spawn14,DOWN);

  InsertEdge(BIG_MAP,M2,M1,Trans21,Spawn21,LEFT);
  InsertEdge(BIG_MAP,M2,M3,Trans23,Spawn23,DOWN);

  InsertEdge(BIG_MAP,M3,M4,Trans34,Spawn34,LEFT);
  InsertEdge(BIG_MAP,M3,M2,Trans32,Spawn32,UP);

  InsertEdge(BIG_MAP,M4,M1,Trans41,Spawn41,UP);
  InsertEdge(BIG_MAP,M4,M3,Trans43,Spawn43,RIGHT);
}
