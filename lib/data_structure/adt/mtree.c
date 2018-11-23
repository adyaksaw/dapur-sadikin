#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "listrek.h"
#include "boolean.h"
#include <conio.h>

int main(){
    BinTree P;
    FILE *fp;
    int X;

    scanf("%d", &X);
    fp = fopen("Temp.txt", "r");
    P = BuildBalanceTree(X, fp);
    PrintTree(P,2);
    fclose(fp);
}