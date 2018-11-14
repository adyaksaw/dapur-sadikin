/*
File : mesinkata.c
Deskripsi : File Implementasi dari mesinkata.h
*/

#include "mesinbaca.h"

Kata CKata;
boolean EndKata;
#include <stdio.h>
/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */
{
  while ((CC == BLANK) && (CC != MARK)){
    ADV();
  }
}

void STARTKATA()
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
  START();
  IgnoreBlank();
  if (CC == MARK)
    EndKata = true;
  else
    SalinKata();

}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
  IgnoreBlank();
  if (CC == MARK)
    EndKata = true;
  else
    SalinKata();
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    int i = 1;
    while (i <= NMax){
      CKata.TabKata[i] = CC;
      ADV();
      if ((CC == BLANK) || (CC == MARK) || (CC == BREAKLINE) ||(CC == BARRIER)){
        break;
      } else {
        ++i;
      }
    }

    if (i == NMax+1){
      CKata.Length = NMax;
      while ((CC != BLANK) && (CC != MARK) && (CC != BREAKLINE) && (CC != BARRIER))
        ADV();
    } else {
      CKata.Length = i;
    }

    IgnoreBlank();
}
