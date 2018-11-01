/* File : map-handler.h */
/* Dapur SADIKIN Map Definition & Handler */

#ifndef MAP_HANDLER_H
#define MAP_HANDLER_H

#include "point.h"

#include "../adt/boolean.h"

#include "../gdt/object.h"

#define MAP_REF_DIR "~dir/map.txt"
#define SAVE_MAP_DIR "~savedir/map.txt"

typedef Object ElType_Map;

typedef struct {
	ElType_Map Mem[MAX_ROW_MAP+1][MAX_COL_MAP+1];
  int NRowEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NColEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matrix;
/* NRowEff <= 1 dan NColEff <= 1 */
/* Indeks matriks yang digunakan: [MIN_ROW_MAP..MAX_ROW_MAP][MIN_COL_MAP..MAX_COL_MAP] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void MakeEmpty_Map (int NB, int NK, Matrix * M);
/* Membuat Map kosong */

/* *** Selektor *** */
boolean IsEmptyPoint_Map (Matriks M, Point p);
/* Mengirimkan true jika i, j tidak diisi objek */

Object CloseToWhat_Map (Matriks M, Point p);


/* ********** KELOMPOK BACA/TULIS ********** */
void Read_Map (Matrix * M, file fptr);
/* I.S. Sembarang */
/* F.S. M terdefinisi nilai berdasar file */
/* Proses: Membaca dari file fptr dan mengisi ke matrix M */
/* Membaca nilai elemen per baris dan kolom */

void Save_Map (Matriks M, file * fptr);
/* I.S. M terdefinisi */
/* F.S. Matriks tersimpan ke dalam file fptr */
/* Proses: Menyimpan Matriks M ke file fptr */

void Print_Map (Matrix M);
/* Print Map ke layar. */

#endif
