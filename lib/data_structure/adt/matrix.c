/* File : matrix.h */
/* Map Matrix of Object */
/* Dapur SADIKIN Map Definition & Handler */

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */

/* Membuat Map kosong */
void MakeEmpty_Map (int NB, int NK, Matrix * M, int RoomID){
  int i,j;
  NRowEff(*M) = NB;
  NColEff(*M) = NK;
  for (i = MIN_ROW_MAP; i <= NB ; ++i ) {
    for (j = MIN_COL_MAP; j <= NK ; ++j ) {
      ElmtMx(*M,i,j).tag = EMPTY;
    }
  }
  (*M).RoomID = RoomID;
}

/* Membuat Meja jadi kosong */
void MakeEmpty_Meja (Matrix *M, int i, int j) {
      ElmtMx(*M,i,j).data.table.customer_here = NULL;
}
/* *** Selektor *** */
boolean IsEmptyPoint_Map (Matrix M, Point p)
/* Mengirimkan true jika i, j tidak diisi objek */
{
  return ElmtMx(M, (int) Absis(p), (int) Ordinat(p)).tag == EMPTY;
}


/* ********** KELOMPOK BACA/TULIS ********** */

void Print_Room (Matrix M)
/* I.S M sudah terdefinisi */
/* F.S Isi M jika isinya objek pada Room, diprint */
{
  int i,j;
  printf("\n\n");
  for (i = MIN_ROW_MAP ; i <= NRowEff(M) ; ++i ) {

    for (j = MIN_COL_MAP ; j <= NColEff(M) ; ++j) {
      if (j == 1) {
        printf("          ");
      }

      if (ElmtMx(M,(i-1),j).tag == TABLE)
        if (IsOccupied(ElmtMx(M,(i-1),j))){ /* Di cek apakah dia sudah occupied atau belum */
          printf("C");
        }else {
          printf("X");
        }
      else if (ElmtMx(M,(i+1),j).tag == TABLE)
        if (IsOccupied(ElmtMx(M,(i+1),j))){
          if (Amount(CustomerAt(ElmtMx(M,(i+1),j))) >= 2){ /* Customer ammount di meja  >= 2*/
            printf("C");
          }else {
            printf("X");
          }
        }else {
          printf("X");
        }
      else if (ElmtMx(M,i,(j+1)).tag == TABLE) {
        if (ElmtMx(M,i,(j+1)).data.table.size != 2 ) /* Kursi = 4 */
          if (IsOccupied(ElmtMx(M,(i),j+1))){
            if (Amount(CustomerAt(ElmtMx(M,(i),j+1))) >= 3){
              printf("C");
            }else {
              printf("X");
            }
          }else {
            printf("X");
          }
        else if (ElmtMx(M,i,j).tag == PLAYER_POS) {
          printf("P");
        } else
          printf("-");
      } else if (ElmtMx(M,i,(j-1)).tag == TABLE) {
        if (ElmtMx(M,i,(j-1)).data.table.size != 2 )
          if (IsOccupied(ElmtMx(M,(i),j-1))){
            if (Amount(CustomerAt(ElmtMx(M,(i),j-1))) == 4){
              printf("C");
            }else {
              printf("X");
            }
          }else {
            printf("X");
          }
        else if (ElmtMx(M,i,j).tag == PLAYER_POS) { /*POSISI PLAYER 'P' */
          printf("P");
        } else
          printf("-");
      } else if (ElmtMx(M,i,j).tag == TABLE) {
        printf("%d",ElmtMx(M,i,j).data.table.num); /*Print Table Number karena TAG = TABLE */
      } else if (ElmtMx(M,i,j).tag == PLAYER_POS) {
        printf("P");
      } else if(ElmtMx(M,i,j).tag == STOVE){
        printf("M");
      } else if(ElmtMx(M,i,j).tag == TRAY){
        printf("T");
      } else {
        printf("-");
      }
      if (j != NColEff(M)) {
        if (ElmtMx(M,i,j).tag == TABLE) {
          if (TableNumber(ElmtMx(M,i,j)) / 10 == 0) //Kalau panjang angka > 2, maka dia langsung dikurangi dengan 1 space
            printf("    ");
          else
            printf("   ");
        } else {
          printf("    ");
        }

      }

    }
    printf("\n\n\n");
  }
}


void Print_Kitchen(Matrix M)
/* I.S M sudah terdefinisi */
/* F.S Isi M jika isinya objek pada Kitchen, diprint */
{

  int i,j;
  for (i = MIN_ROW_MAP ; i <= NRowEff(M) ; ++i ) {
    for (j = MIN_COL_MAP ; j <= NColEff(M) ; ++j) {
      if (ElmtMx(M,i,j).tag == STOVE) /* KOMPOR */
        printf("M");
      else if (ElmtMx(M,i,j).tag == TRAY) /*NAMPAN */
        printf("T");
      else if (ElmtMx(M,i,j).tag == PLAYER_POS) /*PLAYER */
        printf("P");
      else
        printf("-");

      if (j != NColEff(M))
        printf(" ");
    }
    printf("\n");
  }
}

/*Lebih baik pakai ini untuk meneset setiap TAG MATRIX AGAR UNIK, ISI TAG BISA BERUPA PLAYER / OBJEK*/
void SetTag_Matrix(Matrix * M, int i, int j, GameObj Tag){
  ElmtMx(*M, i, j).tag = Tag;
}

/* Selektor untuk elemen matriks */
void SetElement_Matrix(Matrix * M, int i, int j, Object elemenBaru){
  ElmtMx(*M, i, j) = elemenBaru;
}

/* Fungsi untuk mereturn Posisi Player */
Object PlayerObject(){
  Object retVal;
  retVal.tag = PLAYER_POS;
  return retVal;
}
