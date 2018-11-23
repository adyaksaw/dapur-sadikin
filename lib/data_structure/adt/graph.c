#include "graph.h"

void CreateGraph(int X, Graph *L)
{
    First(*L) = AlokNodeG(X);
}

adrNode AlokNodeG(int X, Matrix M)
{
    adrNode G = (adrNode)malloc(sizeof(NodeG));

    if (G != Nil)
    {
        Id(G) = X;
        Room(G) = Nil;
        NPred(G) = 0;
        Trail(G) = Nil;
        Next_Node(G) = Nil;
    }

    return G;
}

void DealokNode(adrNode P)
{
    free(P);
}

adrSuccNode AlokSuccNode(adrNode Pn)
{
    adrSuccNode Pt = malloc(sizeof(SuccNode));

    if (Pt != Nil)
    {
        Succ(Pt) = Pn;
        Next_Trail(Pt) = Nil;
    }
    return Pt;
}

void DealokSuccNode(adrSuccNode P)
{
    free(P);
}

adrNode SearchNodeG(Graph G, int X)
{
    if(First(G) == Nil) return Nil;

    adrNode P = First(G);

    while(P != Nil && Id(G) != X)
        P = Next_Node(P);
    
    return P;
}

adrSuccNode SearchEdge(Graph G, int prec, int succ)
{
    if(First(G) == Nil) return Nil;
    adrNode Pn = SearchNodeG(G, prec);
    
    if(Pn == Nil) return Nil;
    adrSuccNode Pt = Trail(Pn);

    while(Pt != Nil && Id(Succ(Pt)) != succ)
        Pt = Next_Trail(Pt);
    
    return Pt;
}

void InsertNodeG(Graph *G, int X, adrNode *Pn)
{
    
}

void InsertEdge(Graph *G, int prec, int succ)
{
}