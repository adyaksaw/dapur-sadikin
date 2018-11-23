#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "boolean.h"

#define Nil NULL

/* Definisi Type */
typedef struct Node *adrNode;
typedef struct SuccNode *adrSuccNode;
typedef struct {
  int Id;
  int NPred;
  adrSuccNode Trail;
  adrNode Next;
} Node;

typedef struct {
  adrNode Succ;
  adrSuccNode Next;
} SuccNode;

typedef struct {
  adrNode First;
}Graph;


#define Id(Pn) (Pn)->Id
#define NPred(Pn) (Pn)->Next
#define Trail(Pn) (Pn)->Trail
#define Next_Node(Pn) (Pn)->Next
#define Succ(Pt) (Pt)->Succ
#define Next_Trail(Pt) (Pt)->Next

void CreateGraph (int X , Graph *L);

adrNode AlokNode (int X);

void DealokNode (adrNode P);

adrSuccNode AlokSuccNode(adrNode Pn);

void DealokSuccNode(adrSuccNode P);

adrNode SearchNode (Graph G , int X);

adrSuccNode SearchEdge(Graph G, int prec, int succ);

void InsertNode (Graph *G, int X , adrNode *Pn);

void InsertEdge (Graph *G, int prec, int succ);

#endif	