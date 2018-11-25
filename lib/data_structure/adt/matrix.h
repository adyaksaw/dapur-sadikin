/* File : matrix.h */
/* Map Matrix of Object */
/* Dapur SADIKIN Map Definition & Handler */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "boolean.h"
#include "mesinbaca.h"
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
	int RoomID;
} Matrix;
/* NRowEff <= 1 dan NColEff <= 1 */
/* Indeks matriks yang digunakan: [MIN_ROW_MAP..MAX_ROW_MAP][MIN_COL_MAP..MAX_COL_MAP] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

#define NRowEff(M)      (M).NRowEff
#define NColEff(M)      (M).NColEff
#define ElmtMx(M,i,j)   (M).Mem[(i)][(j)]
#define RoomID(M) 			(M).RoomID

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void MakeEmpty_Map (int NB, int NK, Matrix * M, int RoomID);
/* Membuat Map kosong */

void MakeEmpty_Meja ( Matrix *M, int i, int j);
/* *** Selektor *** */
boolean IsEmptyPoint_Map (Matrix M, Point p);
/* Mengirimkan true jika i, j tidak diisi objek */

void Print_Room (Matrix M);
/* Print Map ke layar. */

void Print_Kitchen(Matrix M);
/* I.S M sudah terdefinisi */
/* F.S Isi M jika isinya objek pada Kitchen, diprint */

void SetTag_Matrix(Matrix * M, int i, int j, GameObj Tag);
/*Lebih baik pakai ini!*/

void SetElement_Matrix(Matrix * M, int i, int j, Object elemenBaru);
/*Kalau bisa jangan pakai ini, berbahaya!*/

Object PlayerObject();

#endif
