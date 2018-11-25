#include "graph.h"

void CreateGraph(TypeGraph X, Graph *L)
{
    First(*L) = AlokNode_Graph(X);
}

adrNode AlokNode_Graph(TypeGraph X)
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
{
    free(P);
}

adrSuccNode AlokSuccNode(adrNode Pn, Point Trans, Point Spawn, Direction dir)
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
{
    free(P);
}

adrNode SearchNode_Graph(Graph G, TypeGraph X)
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
  /*
    if (First(G) == Nil)
        return Nil;
    else {
      adrNode P = First(G);
      while (P != Nil && Id(P) != X)
          P = Next_Node(P);
      return P;
    } */
    if (found)
      return P;
    else
      return Nil;
}

adrSuccNode SearchEdge(Graph G, TypeGraph prec, TypeGraph succ)
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
{
  adrNode P,Q;
  adrSuccNode Pn;
    /*if (First(*G) == Nil || SearchEdge(*G, prec, succ) != Nil)
        return;

    adrNode Pn = SearchNode_Graph(*G, prec);

    if (Pn != Nil)
    {
        adrSuccNode Pt = AlokSuccNode(Pn,Trans,Spawn);

        if (Pt != Nil)
        {
            if (Trail(Pn) == Nil)
                Trail(Pn) = Pt;
            else
            {
                adrSuccNode P = Trail(Pn);

                while (Next_Trail(P) != Nil)
                    P = Next_Trail(P);

                Next_Trail(P) = Pt;
            }
        }
    }*/
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
      //printf("TEST1 %f %f\n", Absis(Transition(Pn)), Ordinat(Transition(Pn)) );
    }

    else {
      while (Next_Trail(Pn) != Nil) {
        Pn = Next_Trail(Pn);
      }
      Next_Trail(Pn) = AlokSuccNode(Q,Trans,Spawn,dir);
      //printf("TEST2 %f %f\n", Absis(Transition(Pn)), Ordinat(Transition(Pn)) );
    }

}
