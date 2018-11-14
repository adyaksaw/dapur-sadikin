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

void MakeEmpty_Table (Matrix *M, int i, int j) {
      ElmtMx(*M,i,j).data.table.isOccupied = false;
      CustomerAt(ElmtMx(*M,i,j)).amount = 0;
      CustomerAt(ElmtMx(*M,i,j)).orderID = 0;
      CustomerAt(ElmtMx(*M,i,j)).tableNum.X = 0;
      CustomerAt(ElmtMx(*M,i,j)).tableNum.Y = 0;
      CustomerAt(ElmtMx(*M,i,j)).patience = 0;
      CustomerAt(ElmtMx(*M,i,j)).star = 0;
      CustomerAt(ElmtMx(*M,i,j)).stat = UNDEF;
}
/* *** Selektor *** */
boolean IsEmptyPoint_Map (Matrix M, Point p){}
/* Mengirimkan true jika i, j tidak diisi objek */

ElType_Matrix CloseToWhat_Map (Matrix M, Point p){}


/* ********** KELOMPOK BACA/TULIS ********** */

void Print_Map (Matrix M)
/* Print Map ke layar. */
{
  int i,j;
  for (i = MIN_ROW_MAP ; i <= NRowEff(M) ; ++i ) {
    for (j = MIN_COL_MAP ; j <= NColEff(M) ; ++j) {
      if (ElmtMx(M,i,j).tag== TABLE)
        printf("X");
      else if (ElmtMx(M,i,j).tag == TABLE)
        printf("X");
      else if (ElmtMx(M,i,j).tag == TABLE) {
        if (ElmtMx(M,i,j).data.table.size != 2 )
          printf("X");
        else
          printf("-");
      } else if (ElmtMx(M,i,j).tag == TABLE) {
        if (ElmtMx(M,i,j).data.table.size != 2 )
          printf("X");
        else
          printf("-");
      } else if (ElmtMx(M,i,j).tag == TABLE) {
        printf("%d",ElmtMx(M,i,j).data.table.num);
      } else {
        printf("-");
      }

      if (j != NColEff(M))
        printf(" ");
    }
    printf("_\n");
  }
}
