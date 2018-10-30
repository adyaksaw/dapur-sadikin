/* File : constants.h */
/* Manajemen konstanta & enumerator */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* *** Empty *** */
#define EMPTY 0;

/* ********** STRUKTUR DATA ********** */
/* *** String *** */
#define MIN_STRING 1;

/* *** Integer Table *** */
#define IDX_MAX_TI 100
/* Indeks maksimum array, sekaligus ukuran maksimum array dalam C */
#define IDX_MIN_TI 1
/* Indeks minimum array */
#define IDX_UNDEF_TI -999
/* Indeks tak terdefinisi*/

/* *** Map *** */
/* Ukuran minimum dan maksimum baris dan kolom */
#define MIN_ROW_MAP 1
#define MAX_ROW_MAP 100
#define MIN_COL_MAP 1
#define MAX_COL_MAP 100

/* *** String Stack *** */
#define NULL_STACK_STR 0
#define MAX_ELMT_STACK_STR 10
/* NULL_STACK_STR adalah stack dengan elemen kosong . */
/* Karena indeks dalam bhs C dimulai 0 maka tabel dg indeks 0 tidak dipakai */

/* ********** MAP ********** */
typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
} direction;

/* ********** SORTING ********** */
typedef enum {
	ASC = 1,
	DSC = 2
} sortType;

/* ********** GAME OBJECTS ********** */
typedef enum {
  EMPTY,
  TABLE,
  STOVE,
  TRAY
} gameObj;

#endif