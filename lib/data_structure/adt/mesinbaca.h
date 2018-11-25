/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "boolean.h"
#include "mesinkar.h"
#include <stdio.h>

#define NMax 50
#define BLANK ' '
#define BARRIER '/'
#define SECTION '|'
#define BREAKLINE '\n'

typedef struct {
	char TabKata[NMax+1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : ((CC == BLANK) || (CC == BARRIER) || (CC == BREAKLINE) || (CC == SECTION)) && (CC != MARK)*/

void STARTKATA();
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
          (CC != BREAKLINE), Salin Kata
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK atau (CC == BREAKLINE) ||(CC == BARRIER) || (CC == SECTION)) ;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

void isiKata(Kata * k, char isi[], int isi_length);
/* Mengisi k dengan isi. */

void printKata(Kata k);
/* Menge-print isi dari k tanpa ada karakter tambahan di akhir.*/

void printKataToFile(Kata k, FILE *fp);
/* Memprint Kata yang ada ke file*/

boolean IsKataSama(Kata Kata1 , Kata Kata2);
/* Fungsi mengembalikan apakah Kata1 = Kata2 */

int KataToInt (Kata Kata1);
/* Menkonversi Kata menjadi Integer*/

void IntToKata(int n , Kata* Kata1 );
/* Menkonversi Integer menjadi Kata*/

void normalizeFromFscanf(Kata *Kata1);
/*IdxMin Kata diset menjadi 0 */

#endif
