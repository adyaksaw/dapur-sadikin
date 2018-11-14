/* File : matrix.h */
/* Map Matrix of Object */
/* Dapur SADIKIN Map Definition & Handler */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "point.c"
#include "boolean.h"
#include "mesinbaca.c"
#include "../gdt/static-obj.h"


#define MIN_ROW_MAP 1
#define MAX_ROW_MAP 100
#define MIN_COL_MAP 1
#define MAX_COL_MAP 100

typedef Object ElType_Matrix;

typedef struct {
	ElType_Matrix Mem[MAX_ROW_MAP+1][MAX_COL_MAP+1];
  	int NRowEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NColEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matrix;
/* NRowEff <= 1 dan NColEff <= 1 */
/* Indeks matriks yang digunakan: [MIN_ROW_MAP..MAX_ROW_MAP][MIN_COL_MAP..MAX_COL_MAP] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

#define NRowEff(M)      (M).NRowEff
#define NColEff(M)      (M).NColEff
#define ElmtMx(M,i,j)   (M).Mem[(i)][(j)]

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void MakeEmpty_Map (int NB, int NK, Matrix * M);
/* Membuat Map kosong */

void MakeEmpty_Table ( Matrix *M, int i, int j);
/* *** Selektor *** */
boolean IsEmptyPoint_Map (Matrix M, Point p);
/* Mengirimkan true jika i, j tidak diisi objek */

ElType_Matrix CloseToWhat_Map (Matrix M, Point p);

void Print_Room (Matrix M);
/* Print Map ke layar. */

void Print_Kitchen(Matrix M);


#endif
