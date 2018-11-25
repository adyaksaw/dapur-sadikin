#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "listrek.h"
#include "boolean.h"
#include <conio.h>

int main(){
    BinTree P;
    FILE *fp;
    Item X;

    //Build Balance Tree Modiication
    //AlokNode
    fp = fopen("Temp.txt", "r");
    P = BuildBalanceTree(23, fp);

    //PrintTree
    PrintTree(P,2);
    fclose(fp);

    //Basis
    if (IsTreeEmpty(P)){
        printf("Kosong\n");
    } else {
        printf("Nope\n");
    }
    if (IsTreeOneElmt(P)){
        printf("Satu\n");
    } else {
        printf("Nope\n");
    }

    //SearchItemTree
    X = SearchItemTree(P,2);
    printf("%d %s", ItemID(X),ItemName(X));
}