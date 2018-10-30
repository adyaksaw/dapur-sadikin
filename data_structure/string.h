/* MODUL TABEL CHARACTER */
/* Definisi type string */
/* Berisi definisi dan semua primitif pemrosesan tabel karakter */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel dinamik */

#ifndef STRING_H
#define STRING_H

#include "mgmt/constant.h"
#include "mgmt/namespace.h"
#include "mgmt/selectors.h"

#include "boolean.h"

#include <stdio.h>

typedef struct {
  ElType_Str *T;
  int Neff;
  int MaxEl;
} string;

//For selectors, refer to ~/mgmt/selectors

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty_Str (string * S, int maxel);
/* I.S. S sembarang, maxel > 0 */
/* F.S. Terbentuk tabel S kosong dengan kapasitas maxel + 1 */

/* Destruktor  */
void Destroy_Str (string *S);
/* I.S. S terdefinisi; */
/* F.S. T(S) dikembalikan ke system, MaxEl(S)=0; Neff(S)=0 */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty_Str (string S);
/* Mengirimkan true jika tabel S kosong, mengirimkan false jika tidak */

/* *** Test tabel penuh *** */
boolean IsFull_Str (string S);
/* Mengirimkan true jika tabel S penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void Scan_Str (string *S);
/* I.S. S sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel S terdefinisi */
/* Proses : membaca banyaknya elemen S dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(S) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(S); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk S kosong */

/* *** Mencetak isi tabel *** */
void Print_Str (string S);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. S boleh kosong */
/* F.S. Jika S tidak kosong: e1e2...en */
/* Contoh : jika ada tiga elemen bernilai a, b, c akan dicetak: abc */
/* Jika tabel kosong : tidak mencetak apapun */

/* ********** KONKATENASI ********** */
string Concat_Str (string S1, string S2);
/* Menambahkan S2 di belakang S1.
  Jika salah satu kosong, mengembalikan yang tidak kosong.
  Jika keduanya kosong, mengembalikan tabel kosong.  */

/* ********** OPERATOR RELASIONAL ********** */
boolean IsStr_EQ (string S1, string S2);
/* Mengirimkan true jika S1 sama dengan S2 yaitu jika ukuran S1 = S2 dan semua elemennya sama */

/* ********** OPERASI LAIN ********** */
void Edit_Str (string *S, int maxel);
/* I.S. S sembarang */
/* F.S. S berisi salinan baru dari pengguna (elemen dan ukuran baru) */
/* Proses : Mengosongkan dan membaca ulang ke S */

void Copy_Str (string Sin, string *Sout);
/* I.S. Sin terdefinisi tidak kosong, Sout sembarang */
/* F.S. Sout berisi salinan dari Sin (elemen dan ukuran identik) */
/* Proses : Menyalin isi Sin ke Sout */

/* ********* MENGUBAH UKURAN ARRAY ********* */
void Grow_Str (string *S, int num);
/* Proses : Menambahkan max element sebanyak num */
/* I.S. Tabel sudah terdefinisi */
/* F.S. Ukuran tabel bertambah sebanyak num */

void Shrink_Str (string *S, int num);
/* Proses : Mengurangi max element sebanyak num */
/* I.S. Tabel sudah terdefinisi, ukuran MaxEl > num, dan Neff < MaxEl - num. */
/* F.S. Ukuran tabel berkurang sebanyak num. */

void Compact_Str (string *S);
/* Proses : Mengurangi max element sehingga Neff = MaxEl */
/* I.S. Tabel tidak kosong */
/* F.S. Ukuran MaxEl = Neff */

#endif
