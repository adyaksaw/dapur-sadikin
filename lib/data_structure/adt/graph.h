#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "boolean.h"
#include "matrix.h"
#include "listrek.h"
#include <stdio.h>

#define Nil NULL

/* Definisi Type */
typedef struct gNode *adrNode;
typedef struct SuccNode *adrSuccNode;
typedef struct gNode
{
  int Id;
  Matrix *Room;
  int NPred;
  adrSuccNode Trail;
  adrNode Next;
} Node_Graph;

typedef struct SuccNode
{
  adrNode Succ;
  adrSuccNode Next;
} SuccNode;

typedef struct
{
  adrNode First;
} Graph;

#define First(G) (G).First
#define Id(Pn) (Pn)->Id
#define Room(Pn) (Pn)->Room
#define NPred(Pn) (Pn)->Next
#define Trail(Pn) (Pn)->Trail
#define Next_Node(Pn) (Pn)->Next
#define Succ(Pt) (Pt)->Succ
#define Next_Trail(Pt) (Pt)->Next

void CreateGraph(int X, Graph *L);

adrNode AlokNode_Graph(int X);

void DealokNode_Graph(adrNode P);

adrSuccNode AlokSuccNode(adrNode Pn);

void DealokSuccNode(adrSuccNode P);

adrNode SearchNode(Graph G, int X);

adrSuccNode SearchEdge(Graph G, int prec, int succ);

void InsertNode(Graph *G, int X, adrNode *Pn);

void InsertEdge(Graph *G, int prec, int succ);

#endif