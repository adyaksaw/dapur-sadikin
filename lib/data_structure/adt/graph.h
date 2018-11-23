#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "boolean.h"
#include "matrix.h"
#include "point.h"
#include "listrek.h"
#include <stdio.h>

#define Nil NULL

/* Definisi Type */
typedef Matrix* TypeGraph;
typedef struct gNode *adrNode;
typedef struct SuccNode *adrSuccNode;
typedef struct gNode
{
  TypeGraph Id;
  adrSuccNode Trail;
  adrNode Next;
} Node_Graph;

typedef struct SuccNode
{
  adrNode Succ;
  Point Pos;
  Point Spawn;
  adrSuccNode Next;
} SuccNode;

typedef struct
{
  adrNode First;
} Graph;

#define First(G) (G).First
#define Id(Pn) (Pn)->Id
#define Trail(Pn) (Pn)->Trail
#define Next_Node(Pn) (Pn)->Next
#define Succ(Pt) (Pt)->Succ
#define Transition(Pt) (Pt)->Pos
#define Spawn(Pt) (Pt)->Spawn 
#define Next_Trail(Pt) (Pt)->Next

void CreateGraph(TypeGraph X, Graph *L);

adrNode AlokNode_Graph(TypeGraph X);

void DealokNode_Graph(adrNode P);

adrSuccNode AlokSuccNode(adrNode Pn);

void DealokSuccNode(adrSuccNode P);

adrNode SearchNode_Graph(Graph G, TypeGraph X);

adrSuccNode SearchEdge(Graph G, TypeGraph prec, TypeGraph succ);

void InsertNode_Graph(Graph *G, TypeGraph X, adrNode *Pn);

void InsertEdge(Graph *G, TypeGraph prec, TypeGraph succ);

#endif