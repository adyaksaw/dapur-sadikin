/* File : stack.h */
/* Stack of Items */
/* Deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#include "../data_type.h"
#include "../gdt/item.h"

#include "boolean.h"

#define NULL_STACK_STR 0
#define MAX_ELMT_STACK_STR 10

typedef Item infotype_food;
typedef Item ElType_Stack;
typedef SmallNum Address_Stack;

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct {
	ElType_Stack T[MAX_ELMT_STACK_STR+1]; /* tabel penyimpan elemen */
	Address_Stack TOP;  /* alamat TOP: elemen puncak */
} Stack;
/* Definisi stack S kosong : S.TOP = NULL_STACK_STR */
/* Elemen yang dipakai menyimpan nilai Stack T[1]..T[MAX_ELMT_STACK_STR] */
/* Jika S adalah Stack maka akses elemen : */

#define Top(S)      (S).TOP
#define InfoTop(S)  (S).T[(S).TOP]
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty_Stack (Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MAX_ELMT_STACK_STR */
/* jadi indeksnya antara 1.. MAX_ELMT_STACK_STR+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai NULL_STACK_STR */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty_Stack (Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFull_Stack (Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push_Stack (Stack * S, infotype_food newEl);
/* Menambahkan str sebagai infotype_food baru pada Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. str menjadi name TOP yang baru, ready bernilai false, TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop_Stack (Stack * S, infotype_food * X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

/* ********** KELOMPOK BACA/TULIS ********** */
void Input_Stack (Stack * S, FILE * fptr);
/* Membaca Stack S dari FILE teks eksternal. */
/* I.S. S sembarang */
/* F.S. Save FILE fptr masuk ke Stack S */

void Save_Stack (Stack * S, FILE * fptr);
/* Menyimpan Stack S ke FILE teks eksternal. */
/* I.S. S terdefinisi */
/* F.S. Stack S terdefinisi ke FILE fptr */

void PrintData_Stack (Stack S);
/* Proses : Menuliskan data dari FILE eksternal yang terkait dengan isi stack */
/* I.S. S boleh kosong */
/* F.S. Jika S tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika S kosong : Hanya menulis "/Array name/ is empty." */
/* Contoh: Jika isi Stack: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]Spaghetti
   [2}Sosis
   [3]Piring
   [4]Garpu
*/

Stack Reverse_Stack(Stack *S);

#endif
