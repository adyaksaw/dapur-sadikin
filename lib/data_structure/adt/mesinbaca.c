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
  while (((CC == BLANK) || (CC == BARRIER) || (CC == BREAKLINE)) && (CC != MARK)){
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
  else {
    SalinKata();
  }


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
  else if ((CC != BREAKLINE) && (CC != BARRIER))
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
      //printf("Isi dari CKata.TabKata[%d] %c\n",i, CKata.TabKata[i]);
      ADV();
      if ((CC == BLANK) || (CC == MARK) || (CC == BREAKLINE) ||(CC == BARRIER)){
        break;
      } else {
        ++i;
      }
    }

    //printf("%s",CKata.TabKata);

    if (i == NMax+1){
      CKata.Length = NMax;
      while ((CC != BLANK) && (CC != MARK) && (CC != BREAKLINE) && (CC != BARRIER))
        ADV();
    } else {
      CKata.Length = i;
    }

}

boolean IsKataSama(Kata Kata1 , Kata Kata2) {
  int i;
  boolean sama = true;
  if (Kata1.Length != Kata2.Length) {
    sama = false;
  } else {
    for (i = 1 ; i <= Kata1.Length ; ++i) {
      if (Kata1.TabKata[i] != Kata2.TabKata[i]) {
        sama = false;
        break;
      }
    }
  }
  return sama;
}

int KataToInt (Kata Kata1) {
  int hsl = 0;
  int i;
  if (Kata1.Length == 1)
    hsl = Kata1.TabKata[1] - '0';
  else {
    for (i = 1 ; i <= Kata1.Length ; ++i)
      hsl = hsl * 10 + (Kata1.TabKata[i] - '0');
  }
}

void IntToKata(int n , Kata *Kata1 ) {
  int hsl =n;
  int mod = 0;
  int i = 0;
  while (n > 0) {
    n = n / 10;
    ++i; //Cari panjang integer
  }
  (Kata1)->Length = i;
  while (hsl > 0) {
    mod = hsl % 10;
    (Kata1)->TabKata[i] = '0' + mod;
    hsl = hsl/10;
    --i;
  }


}
