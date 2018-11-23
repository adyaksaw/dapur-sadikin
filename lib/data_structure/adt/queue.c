/* File : queue.c */
/* Queue of Customer */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "../gdt/customer.h"
#include "queue.h"

/* Definisi Queue kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* Prototype ********* */
boolean IsEmpty_Queue (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    /*Kamus Lokal*/
    // -

    /*Algoritma*/
    return ((Head(Q) == Nil_Queue) && (Tail(Q) == Nil_Queue));
}

boolean IsFull_Queue (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    /*Kamus Lokal*/
    // -

    /*Algoritma*/
    return (NBElmt_Queue(Q) == MaxEl(Q));
}
int NBElmt_Queue (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    /*Kamus Lokal*/
    // -

    /*Algoritma*/
    if (IsEmpty_Queue(Q)){
        return 0;
    } else if (Head(Q) <= Tail(Q)){
        return(Tail(Q) - Head(Q) + 1);
    } else {
        return (MaxEl(Q) + Tail(Q) - Head(Q) + 1);
    }
}
/* *** Kreator *** */
void CreateEmpty_Queue (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
    /* Kamus Lokal */
    /* Algoritma */
    (*Q).T = malloc ((Max+1) * sizeof(ElType_Queue));
    if ((*Q).T != NULL) {
        MaxEl(*Q) = Max;
        Head(*Q) = Nil_Queue;
        Tail(*Q) = Nil_Queue;
    } else /* alokasi gagal */ {
        MaxEl(*Q) = 0;
    }
}
/* *** Destruktor *** */
void DeAlokasi_Queue(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    /*Kamus Lokal*/
    // -

    /*Algoritma*/
    ElType_Queue current_elmt;
    while (!IsEmpty_Queue(*Q)){
        printf("NOTEMPTY\n");
        Del_Queue(Q, &current_elmt);
        Dealokasi_Customer(current_elmt);
    }

    if (IsEmpty_Queue(*Q)){
        printf("QUEUE sudah empty.\n");
    }else {
        printf("BEWARE MEMORY LEAK!\n");
    }
    MaxEl(*Q) = 0;
    free((*Q).T);
}
/* *** Primitif Add/Delete *** */
void Add_Queue (Queue * Q, ElType_Queue * X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
    /* Kamus Lokal */
    Address_Queue i;

    /* Algoritma */
    if (IsEmpty_Queue(*Q)) {
        Head(*Q)=1;
        Tail(*Q)=1;
        InfoTail(*Q)=*X;
    } else /* Q tidak kosong */ {
        if (Priority(*(*X)) == 0){
            if (Tail(*Q) == MaxEl(*Q)) {
                Tail(*Q) = 1;
            } else {
                Tail(*Q)++;
            }
            InfoTail(*Q) = *X;
        } else {
            if (Head(*Q) == 1){
                Head(*Q) = MaxEl(*Q);
            } else {
                Head(*Q)--;
            }
            InfoHead(*Q) = *X;
            i = Head(*Q);
            while (Priority(*ElmtQ(*Q,i)) <= Priority(*ElmtQ(*Q,i+1))){
                ElType_Queue temp = ElmtQ(*Q,i+1);
                ElmtQ(*Q,i+1) = ElmtQ(*Q,i);
                ElmtQ(*Q,i) = temp;
                if (i == MaxEl(*Q)){
                    i = 1;
                } else { 
                    i++;
                }
            }
        }
    }
}
void Del_Queue (Queue * Q, ElType_Queue * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
{
    /* Kamus Lokal */
    /* Algoritma */
    *X = InfoHead(*Q);
    if ((Head(*Q) != Nil_Queue) && (Tail(*Q) != Nil_Queue) && (Head(*Q) == Tail(*Q))){
        Head(*Q) = Nil_Queue;
        Tail(*Q) = Nil_Queue;
    }else if(Head(*Q) == MaxEl(*Q)){
        Head(*Q) = 1;
    }else {
        Head(*Q)++;
    }
}

void normalizedQueue(Queue * Q, Address_Queue emptyEl){
    if(NBElmt_Queue(*Q) == 1){
        CreateEmpty_Queue(Q, MaxEl(*Q));
    } else {
        while(emptyEl != Tail(*Q)){
            (*Q).T[emptyEl] = (*Q).T[1+(emptyEl%MaxEl(*Q))];
            emptyEl = 1+(emptyEl%MaxEl(*Q));
        }
        Tail(*Q)--;
        if(Tail(*Q) == 0){
            Tail(*Q) = MaxEl(*Q);
        }
    }
}

void Print_Queue(Queue Q){
    printf("Customer di Queue:\n");
    int HeadID = Head(Q);
    if (HeadID < Tail(Q)){
        while (HeadID <= Tail(Q)){
            printCustomer(*(Q.T[HeadID]));
            HeadID++;
        }
    }else if (HeadID > Tail(Q)){
        while (HeadID != Tail(Q)){
            printCustomer(*(Q.T[HeadID]));
            HeadID++;
            if (HeadID == MaxEl(Q)){
                HeadID = 1;
            }
        }
        if (HeadID == Tail(Q)){
            printCustomer(*(Q.T[HeadID]));
        }
    }else {
        if (HeadID != Nil_Queue && HeadID == Tail(Q)){
            printCustomer(*(Q.T[HeadID]));
        }else {
            printf("Queue kosong.\n");
        }
    }
}
