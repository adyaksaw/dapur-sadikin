#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include "boolean.h"

int main(){
    Queue Q;
    
    Customer *Y = malloc(sizeof(Customer));

    //Crate Empty
    CreateEmpty_Queue(&Q, 5);

    //IsEmpty_Queue
    if (IsEmpty_Queue(Q)){
        printf("Empty Queue\n");
    } else {
        printf("Not Empty\n");
    }

    //Add_Queue
    for (int i= 1; i <= 5; i++){
        Customer *X = malloc(sizeof(Customer));
        scanf("%d", &(*X).amount);
        scanf("%d", &(*X).star);
        (*X).stat = 0;
        (*X).orderID = 0;
        (*X).patience = 0;
        (*X).tableNum = 0;
        Add_Queue(&Q,X);
    }

    //Is_Full & PrintQueue
    if (IsFull_Queue(Q)){
        Print_Queue(Q);
    }

    //DelQueue
    Del_Queue(&Q,&Y);

    //NBElmt_Queue
    int N = NBElmt_Queue(Q);
    printf("%d", N);
}
