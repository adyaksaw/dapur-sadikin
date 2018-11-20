/*
    Nama        :   Aidil Rezjki Suljztan Syawaludin
    NIM         :   13517070
    Tanggal     :   7 November 2018
    Topik       :   ADT - List Rekursif
    Deskripsi   :   Realisasi dari file header listrek.h
*/

#include <stdio.h>
#include <stdlib.h>

#include "listrek.h"

/* *** Manajemen Memori *** */
address Alokasi_ListRek (infotype X){
    /* Mengirimkan address hasil alokasi sebuah elemen */
    /* Jika alokasi berhasil, maka address tidak Nil, dan misalnya menghasilkan P, 
    maka Info(P) = X, Next(P) = Nil */
    /* Jika alokasi gagal, mengirimkan Nil */
    address NewElmt = malloc(sizeof(ElmtList));

    if (NewElmt != Nil){
        Info(NewElmt) = X;
        Next(NewElmt) = Nil;
        return NewElmt;
    }else {
        return Nil;
    }
}
void Dealokasi_ListRek (address P){
    /* I.S. P terdefinisi */
    /* F.S. P dikembalikan ke sistem */
    /* Melakukan dealokasi/pengembalian address P */
    free(P);
}

/* *** Primitif-primitif yang harus direalisasikan *** */

/* Pemeriksaan Kondisi List */
int IsEmpty_ListRek(List L){
    /* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */
    if (L == Nil){
        return 1;
    }else {
        return 0;
    }
}
int IsOneElmt_ListRek(List L){
    /* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */
    if (!IsEmpty_ListRek(L) && Next(L) == Nil){
        return 1;
    }else {
        return 0;
    }
}

/* *** Selektor *** */
infotype FirstElmt_ListRek (List L){
    /* Mengirimkan elemen pertama sebuah list L yang tidak kosong */
    if (!IsEmpty_ListRek(L)){
        return Info(L);
    }else {
        return -999;
    }
}
List Tail_ListRek(List L){
    /* Mengirimkan list L tanpa elemen pertamanya, mungkin menjadi list kosong */
    if (!IsEmpty_ListRek(L)){
        return Next(L);
    }else {
        return Nil;
    }
}

/* *** Konstruktor *** */
List Konso_ListRek(infotype e, List L){
    /* Mengirimkan list L dengan tambahan e sebagai elemen pertamanya. 
    e dialokasi terlebih dahulu. Jika alokasi gagal, mengirimkan L. */
    List NewElmt = Alokasi_ListRek(e);
    if (NewElmt != Nil){
        Next(NewElmt) = L;
        return NewElmt;
    }else {
        return L;
    }
}
List KonsB_ListRek(List L, infotype e){
    /* Mengirimkan list L dengan tambahan e sebagai elemen pertamanya */
    /* e harus dialokasi terlebih dahulu */
    /* Jika alokasi e gagal, mengirimkan L */ 
    if (!IsEmpty_ListRek(L)){
        List NewElmt = Alokasi_ListRek(e);
        if (NewElmt != Nil){
            List CurrentElmt = L;
            while (Next(CurrentElmt) != Nil){
                CurrentElmt = Next(CurrentElmt);
            }
            Next(CurrentElmt) = NewElmt;
        }
        return L;
    }else {
        Konso_ListRek(e, L);
    }
}

/* *** Operasi Lain *** */
List Copy_ListRek (List L){
    /* Mengirimkan salinan list L (menjadi list baru) */
    /* Jika ada alokasi gagal, mengirimkan L */ 
    if (!IsEmpty_ListRek(L)){
        List CurrentElmt = L;

        List NewList = Alokasi_ListRek(Info(CurrentElmt));
        boolean Successful = NewList != Nil;

        if (Successful){
            List NewElmt = NewList;
            CurrentElmt = Next(CurrentElmt);

            while (CurrentElmt != Nil && Successful){
                List Temp = Alokasi_ListRek(Info(CurrentElmt));
                Successful = Temp != Nil;
                if (Successful){
                    Next(NewElmt) = Temp;
                    NewElmt = Temp;
                    CurrentElmt = Next(CurrentElmt);
                }
            }

            if (Successful){
                return NewList;
            }else {
                return L;
            }
        }else {
            return L;
        }
    }else {
        return L;
    }
}
void MCopy_ListRek (List Lin, List *Lout){
    /* I.S. Lin terdefinisi */
    /* F.S. Lout berisi salinan dari Lin */
    /* Proses : menyalin Lin ke Lout */
    (*Lout) = Copy_ListRek(Lin);
}
List Concat_ListRek (List L1, List L2){
    /* Mengirimkan salinan hasil konkatenasi list L1 dan L2 (menjadi list baru) */
    /* Jika ada alokasi gagal, menghasilkan Nil */
    if (!IsEmpty_ListRek(L1) && !IsEmpty_ListRek(L2)){
        List NewList = Copy_ListRek(L1);

        List NewElmt = NewList;
        while(Next(NewElmt) != Nil){
            NewElmt = Next(NewElmt);
        }
        Next(NewElmt) = Copy_ListRek(L2);

        return NewList;
    }else {
        if (IsEmpty_ListRek(L1)){
            if (IsEmpty_ListRek(L2)){
                return Nil;
            }else {
                return Copy_ListRek(L2);
            }
        }else {
            return Copy_ListRek(L1);
        }
    }
}
void MConcat_ListRek (List L1, List L2, List *LHsl){
    /* I.S. L1, L2 terdefinisi */
    /* F.S. LHsl adalah hasil melakukan konkatenasi L1 dan L2 dengan cara "disalin" */
    /* Proses : Menghasilkan salinan hasil konkatenasi list L1 dan L2 */

    (*LHsl) = Concat_ListRek(L1, L2);
}
void PrintList_ListRek (List L){
    /* I.S. L terdefinisi. */
    /* F.S. Setiap elemen list dicetak. */
    if (!IsEmpty_ListRek(L)){
        List CurrentElmt = L;
        while (CurrentElmt != Nil){
            printf("%d\n", Info(CurrentElmt));
            CurrentElmt = Next(CurrentElmt);
        }
    }
}
int NbElmtList_ListRek (List L){
    /* Mengirimkan banyaknya elemen list L, Nol jika L kosong */
    List CurrentElmt = L;
    int count = 0;

    while(CurrentElmt != Nil){
        count++;
        CurrentElmt = Next(CurrentElmt);
    }
    
    return count;

    /*
    if (!IsEmpty_ListRek(L)){
        List CurrentElmt = L;
        int count = 0;

        while(CurrentElmt != Nil){
            count++;
            CurrentElmt = Next(CurrentElmt);
        }
        
        return count;
    }else {
        return 0;
    }
    */
}
boolean Search_ListRek (List L, infotype X){
    /* Mengirim true jika X adalah anggota list, false jika tidak */
    if (!IsEmpty_ListRek(L)){
        List CurrentElmt = L;

        while (Info(CurrentElmt) != X && Next(CurrentElmt) != Nil){
            CurrentElmt = Next(CurrentElmt);
        }

        return Info(CurrentElmt) == X;
    }else {
        return false;
    }
}