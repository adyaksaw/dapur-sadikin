/* File : matrix.h */
/* Map Matrix of Object */
/* Dapur SADIKIN Map Definition & Handler */

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void MakeEmpty_Map (int NB, int NK, Matrix * M){
  int i,j;
  NRowEff(*M) = NB;
  NColEff(*M) = NK;
  for (i = MIN_ROW_MAP; i <= NB ; ++i ) {
    for (j = MIN_COL_MAP; j <= NK ; ++j ) {
      ElmtMx(*M,i,j).tag = EMPTY;
    }
  }
}
/* Membuat Map kosong */

void MakeEmpty_Meja (Matrix *M, int i, int j) {
      ElmtMx(*M,i,j).data.table.customer_here = NULL;

}
/* *** Selektor *** */
boolean IsEmptyPoint_Map (Matrix M, Point p)
/* Mengirimkan true jika i, j tidak diisi objek */
{
  return ElmtMx(M, (int) Absis(p), (int) Ordinat(p)).tag == EMPTY;
}

ElType_Matrix CloseToWhat_Map (Matrix M, Point p)
{

}


/* ********** KELOMPOK BACA/TULIS ********** */

void Print_Room (Matrix M)
/* Print Map ke layar. */
{
  int i,j;
  for (i = MIN_ROW_MAP ; i <= NRowEff(M) ; ++i ) {
    for (j = MIN_COL_MAP ; j <= NColEff(M) ; ++j) {
      if (ElmtMx(M,(i-1),j).tag== TABLE)
        printf("X");
      else if (ElmtMx(M,(i+1),j).tag == TABLE)
        printf("X");
      else if (ElmtMx(M,i,(j+1)).tag == TABLE) {
        if (ElmtMx(M,i,(j+1)).data.table.size != 2 )
          printf("X");
        else
          printf("-");
      } else if (ElmtMx(M,i,(j-1)).tag == TABLE) {
        if (ElmtMx(M,i,(j-1)).data.table.size != 2 )
          printf("X");
        else
          printf("-");
      } else if (ElmtMx(M,i,j).tag == TABLE) {
        printf("%d",ElmtMx(M,i,j).data.table.num);
      } else if (ElmtMx(M,i,j).tag == PLAYER_POS) {
        printf("P");
      } else {
        printf("-");
      }

      if (j != NColEff(M))
        printf(" ");
    }
    printf("\n");
  }
}

void Print_Kitchen(Matrix M) {
  int i,j;
  for (i = MIN_ROW_MAP ; i <= NRowEff(M) ; ++i ) {
    for (j = MIN_COL_MAP ; j <= NColEff(M) ; ++j) {
      if (ElmtMx(M,i,j).tag == STOVE)
        printf("M");
      else if (ElmtMx(M,i,j).tag == TRAY)
        printf("T");
      else if (ElmtMx(M,i,j).tag == PLAYER_POS)
        printf("P");
      else
        printf("-");

      if (j != NColEff(M))
        printf(" ");
    }
    printf("\n");
  }
}

void SetElement_Matrix(Matrix * M, int i, int j, Object elemenBaru){
  ElmtMx(*M, i, j) = elemenBaru;
}

Object PlayerObject(){
  Object retVal;
  retVal.tag = PLAYER_POS;
  return retVal;
}
