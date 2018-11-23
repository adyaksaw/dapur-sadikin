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
}

void DealokNode_Graph(adrNode P)
{
    free(P);
}

adrSuccNode AlokSuccNode(adrNode Pn)
{
    adrSuccNode Pt = malloc(sizeof(SuccNode));

    if (Pt != Nil)
    {
        Succ(Pt) = Pn;
        Transition(Pt) = MakePoint(-1, -1); //hardcode when use
        Spawn(Pt) = MakePoint(-1, -1);
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
    if (First(G) == Nil)
        return Nil;

    adrNode P = First(G);

    while (P != Nil && Id(P) != X)
        P = Next_Node(P);

    return P;
}

adrSuccNode SearchEdge(Graph G, TypeGraph prec, TypeGraph succ)
{
    if (First(G) == Nil)
        return Nil;
    adrNode Pn = SearchNodeG(G, prec);

    if (Pn == Nil)
        return Nil;
    adrSuccNode Pt = Trail(Pn);

    while (Pt != Nil && Id(Succ(Pt)) != succ)
        Pt = Next_Trail(Pt);

    return Pt;
}

void InsertNode_Graph(Graph *G, TypeGraph X, adrNode *Pn)
{
    if (SearchNode_Graph(*G, X) != Nil)
        return;

    *Pn = AlokNode_Graph(X);

    if (*Pn != Nil)
    {
        if (First(*G) == Nil)
            First(*G) = *Pn;
        else
        {
            adrNode P = First(*G);

            while (Next_Node(P) != Nil)
                P = Next_Node(P);

            Next_Node(P) = *Pn;
        }
    }
}

void InsertEdge(Graph *G, TypeGraph prec, TypeGraph succ)
{
    if (First(*G) == Nil || SearchEdge(*G, prec, succ) != Nil)
        return;

    adrNode Pn = SearchNode_Graph(*G, prec);

    if (Pn != Nil)
    {
        adrSuccNode Pt = AlokSuccNode(Pn);

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
    }
}