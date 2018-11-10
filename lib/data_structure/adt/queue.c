/* File : queue.c */
/* Queue of Customer */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "../gdt/customer.h"

/* Definisi Queue kosong: HEAD=Nil; TAIL=Nil. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    /*Kamus Lokal*/
    // - 

    /*Algoritma*/
    return ((Head(Q) == Nil_Queue) && (Tail(Q) == Nil_Queue));
}

boolean IsFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    /*Kamus Lokal*/
    // - 

    /*Algoritma*/
    return (NBElmt(Q) == MaxEL(Q));
}
int NBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    /*Kamus Lokal*/
    // - 

    /*Algoritma*/
    if (IsEmpty(Q)){
        return 0;
    } else if (Head(Q) <= Tail(Q)){
        return(Tail(Q) - Head(Q) + 1);
    } else {
        return (MaxEl(Q) + Tail(Q) - Head(Q) + 1);
    }
}
/* *** Kreator *** */
void CreateEmpty (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{ 
    /* Kamus Lokal */
    /* Algoritma */
    (*Q).T = (infotype *) malloc ((Max+1) * sizeof(infotype));
    if ((*Q).T != NULL) {
        MaxEl(*Q) = Max;
        Head(*Q) = Nil_Queue;
        Tail(*Q) = Nil_Queue;
    } else /* alokasi gagal */ {
        MaxEl(*Q) = 0;
    }
}
/* *** Destruktor *** */
void DeAlokasi(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    /*Kamus Lokal*/
    // - 

    /*Algoritma*/
    free((*Q).T);
    MaxEl(*Q) = 0;
}
/* *** Primitif Add/Delete *** */
void Add (Queue * Q, ElType_Queue X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
    /* Kamus Lokal */
    Address_Queue i, j;

    /* Algoritma */
    if (IsEmpty(*Q)) {
        Head(*Q)=1;
        Tail(*Q)=1;
    } else /* Q tidak kosong */ {
        if (Tail(*Q) == MaxEl(*Q)) { /* Geser elemen smp Head(Q)=1 */
            Tail(*Q) = 1;
        } else {
            Tail(*Q)++;
        }
    }
    InfoTail(*Q)=X;
}
void Del (Queue * Q, ElType_Queue * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
{
    /* Kamus Lokal */
    /* Algoritma */
    *X = InfoHead(*Q);
    if(Head(*Q) == MaxEl(*Q)){
        Head(*Q) = 1;
    } else if ((Head(*Q) == 1) && (Tail(*Q) == 1)){
        Head(*Q) = Nil_Queue;
        Tail(*Q) = Nil_Queue;
    } else {
        Head(*Q)++;
    }
}