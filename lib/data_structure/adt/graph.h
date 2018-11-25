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
typedef struct gSuccNode *adrSuccNode;
typedef struct gNode
{
  TypeGraph Id;
  adrSuccNode Trail;
  adrNode Next;
} Node_Graph;

/* Arah player akan bergerak kemana saja */
typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT,
} Direction;


typedef struct gSuccNode
{
  adrNode Succ;
  Point Pos;
  Point Spawn;
  Direction dir;
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
#define Dir(Pt) (Pt)->dir
#define Next_Trail(Pt) (Pt)->Next

void CreateGraph(TypeGraph X, Graph *L);
/* Membuat sebuah graf L*/

adrNode AlokNode_Graph(TypeGraph X);
/* Mengalokasikan Node pada Graph, mereturn address tidak Nil kalau berhasil dialokasi */

void DealokNode_Graph(adrNode P);
/* Mendealokasikan Node pada Graph, memori dikembalikan ke sistem */

adrSuccNode AlokSuccNode(adrNode Pn, Point Trans, Point Spawn, Direction dir);
/* Mengalokasikan SuccNode sehingga dapat terbentuk Edge */

void DealokSuccNode(adrSuccNode P);
/* Mendealokasikan SuccNode pada Graph, memori dikembalikan ke sistem */

adrNode SearchNode_Graph(Graph G, TypeGraph X);
/* Menngembalikan address yang berisi X pada Node di Graph,
jika tidak ditemukan akan dikembalikan Nil */

adrSuccNode SearchEdge(Graph G, TypeGraph prec, TypeGraph succ);
/* Menngembalikan address yang berasal dari prec dan menuju ke succ
pada SearchNode di Graph, jika tidak ditemukan akan dikembalikan Nil */

void InsertNode_Graph(Graph *G, TypeGraph X, adrNode *Pn);
/* Memasukkan Node pada Graph G dengan isi X dan Pn berisi dengan address Node tersebut */


void InsertEdge(Graph *G, TypeGraph prec, TypeGraph succ, Point Trans, Point Spawn, Direction dir);
/* Memasukkan Edge Baru pada graf G, yang berasal dari prec dan menuju ke succ.
Isi adalah Trans -> Posisi player sekarang di ruangan sekarang, Spawn -> Posisi player nanti di ruangan
baru, Dir -> Direction dari player (GU/GL/GD/GR) */

#endif
