/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi I : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel statik */

#ifndef ARRAY_INT_H
#define ARRAY_INT_H

#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"

#include "../gdt/item.h"

/* *** Integer Table *** */
#define IDX_MAX_TI 100
/* Indeks maksimum array, sekaligus ukuran maksimum array dalam C */
#define IDX_MIN_TI 1
/* Indeks minimum array */

typedef int IdxType_Table;
typedef Item ElType_Table;   /* type elemen tabel */

typedef enum {
	ASC = 1,
	DSC = 2
} SortType;

/* Definisi elemen dan koleksi objek */
typedef struct {
	ElType_Table T[IDX_MAX_TI + 1]; /* memori tempat penyimpan elemen (container) */
	int NEff; /* >=0, banyaknya elemen efektif */
} Table;
/* Indeks yang digunakan [IDX_MIN_TI..IDX_MAX_TI] */
/* Jika T adalah Table, cara deklarasi dan akses: */
/* Deklarasi : T : Table */
/* Maka cara akses:
   T.Neff  untuk mengetahui banyaknya elemen
   T.T    untuk mengakses seluruh nilai elemen tabel
   T.T[i] untuk mengakses elemen ke-i */

#define NEff(X)     (X).NEff
#define Array(X)    (X).T
#define Elmt(X,i)   (X).T[(i)]
/* Definisi :
  Tabel kosong: T.Neff = 0
  Definisi elemen pertama : T.T[i] dengan i=1
  Definisi elemen terakhir yang terdefinisi: T.T[i] dengan i=T.Neff */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty_Table (Table * T);
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IDX_MAX_TI-IDX_MIN_TI+1 */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty_Table (Table T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */

/* *** Test tabel penuh *** */
boolean IsFull_Table (Table T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */


/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void Input_Table (Table * T, file * fptr);
/* Membaca Table dari file teks eksternal. */
/* I.S. T sembarang */
/* F.S. Save file fptr masuk ke Table T */

void Save_Table (Table T, file * fptr);
/* Menyimpan Table ke file teks eksternal. */
/* I.S. T terdefinisi */
/* F.S. Table T tersimpan ke file fptr */

void PrintData_Table (Table T);
/* Proses : Menuliskan data dari file eksternal yang terkait dengan isi tabel */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika T kosong : Hanya menulis "/Array name/ is empty." */
/* Contoh: Jika isi Tabel: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]Spaghetti
   [2}Sosis
   [3]Piring
   [4]Garpu
*/

/* ********** SORTNG ********** */
void Sort_Table (Table * T, sortType x);
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut berdasarkan sortType */
/* Proses : mengurutkan T sehingga elemennya menurun/mengecil */

/* ***  Perhatian : Tabel boleh kosong!! Tabel TERURUT!! *** */
/* ********** SEARCHING ********** */
IdxType_Table Search_Table (Table T, IdxType_Table X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IDX_UNDEF_TI */
/* Menghasilkan indeks tak terdefinisi (IDX_UNDEF_TI) jika tabel T kosong */

boolean FoundIn_Table (Table T, IdxType_Table X);
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */

IdxType_Table Max_Table (Table T);
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai maksimum pada tabel */

IdxType_Table Min_Table (Table T);
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai minimum pada tabel*/

/* ***  Perhatian : Tabel boleh kosong!! Tabel TERURUT!! *** */

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void Append_Table (Table * T, IdxType_Table X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
void DelEli_Table (Table * T, IdxType_Table i, IdxType_Table * X);
/* Menghapus elemen ke-i tabel tanpa mengganggu kontiguitas */
/* I.S. Tabel tidak kosong, i adalah indeks efektif yang valid */
/* F.S. X adalah nilai elemen ke-i T sebelum penghapusan */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
/* Proses : Geser elemen ke-i+1 s.d. elemen terakhir */
/*          Kurangi elemen efektif tabel */

#endif
