#include "graph.h"

void CreateGraph(TypeGraph X, Graph *L)
/* Membuat sebuah graf L */
{
    First(*L) = AlokNode_Graph(X);
}

adrNode AlokNode_Graph(TypeGraph X)
/* Mengalokasikan Node pada Graph, mereturn address tidak Nil kalau berhasil dialokasi */
{
    adrNode G = (adrNode)malloc(sizeof(Node_Graph));

    if (G != Nil)
    {
        Id(G) = X;
        Trail(G) = Nil;
        Next_Node(G) = Nil;
    }

    return G;
}

void DealokNode_Graph(adrNode P)
/* Mendealokasikan Node pada Graph, memori dikembalikan ke sistem */
{
    free(P);
}

adrSuccNode AlokSuccNode(adrNode Pn, Point Trans, Point Spawn, Direction dir)
/* Mengalokasikan SuccNode sehingga dapat terbentuk Edge */
{
    adrSuccNode Pt = (adrSuccNode) malloc(sizeof(SuccNode));

    if (Pt != Nil)
    {
        Succ(Pt) = Pn;
        Transition(Pt) = Trans; //hardcode when use
        Dir(Pt) = dir;
        Spawn(Pt) = Spawn;
        Next_Trail(Pt) = Nil;
    }
    return Pt;
}

void DealokSuccNode(adrSuccNode P)
/* Mendealokasikan SuccNode pada Graph, memori dikembalikan ke sistem */
{
    free(P);
}

adrNode SearchNode_Graph(Graph G, TypeGraph X)
/* Menngembalikan address yang berisi X pada Node di Graph,
jika tidak ditemukan akan dikembalikan Nil */
{
  boolean found = false;
  adrNode P;
  P = First(G);
  if (P == Nil)
    return Nil;
  else {
    while ((P != Nil) && (!found)) {
      if (Id(P) == X)
        found = true;
      else
        P = Next_Node(P);
    }
  }

    if (found)
      return P;
    else
      return Nil;
}

adrSuccNode SearchEdge(Graph G, TypeGraph prec, TypeGraph succ)
/* Menngembalikan address yang berasal dari prec dan menuju ke succ
pada SearchNode di Graph, jika tidak ditemukan akan dikembalikan Nil */
{
    boolean found = false;
    adrSuccNode Pt ;
    adrNode Pn = SearchNode_Graph(G, prec);
    if (Pn == Nil)
      return Nil;
    else {
      Pt = Trail(Pn);
      while ((Pt != Nil) && (!found)){
        if (Id(Succ(Pt)) == succ)
          found = true;
        else
          Pt = Next_Trail(Pt);
      }
    }

    if (found)
      return Pt;
    else
      return Nil;
}

void InsertNode_Graph(Graph *G, TypeGraph X, adrNode *Pn)
/* Memasukkan Node pada Graph G dengan isi X dan Pn berisi dengan address Node tersebut */
{

    adrNode P;
    if (First(*G) == Nil) {
      P = AlokNode_Graph(X);
      if (P != Nil){
        First(*G) = P;
        *Pn = First(*G);
      }
      else {
        *Pn = Nil;
      }
    } else {
      P = First(*G);
      while (Next_Node(P) != Nil) {
        P = Next_Node(P);
      }
      Next_Node(P) = AlokNode_Graph(X);
      *Pn = P;
    }
}

void InsertEdge(Graph *G, TypeGraph prec, TypeGraph succ, Point Trans, Point Spawn, Direction dir)
/* Memasukkan Edge Baru pada graf G, yang berasal dari prec dan menuju ke succ.
Isi adalah Trans -> Posisi player sekarang di ruangan sekarang, Spawn -> Posisi player nanti di ruangan
baru, Dir -> Direction dari player (GU/GL/GD/GR) */
{
  adrNode P,Q;
  adrSuccNode Pn;

    Q = SearchNode_Graph(*G,succ);
    P = SearchNode_Graph(*G,prec);
    if (P == Nil) {
      InsertNode_Graph(G,prec,&P);
      printf("Tes P\n");
    }

    if (Q == Nil){
      printf("Tes Q\n");
      InsertNode_Graph(G,succ,&Q);

    }

    Pn = Trail(P);
    if (Pn == Nil) {
      Trail(P) = AlokSuccNode(Q,Trans,Spawn,dir);
      Pn = Trail(P);

    }

    else {
      while (Next_Trail(Pn) != Nil) {
        Pn = Next_Trail(Pn);
      }
      Next_Trail(Pn) = AlokSuccNode(Q,Trans,Spawn,dir);
    }

}
