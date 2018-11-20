/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */
/* Penamaan type infotype, type addrNode, dan beberapa fungsi disesuikan 
   karena melibatkan modul list rekursif. */

/* *** PROTOTYPE *** */
#include "listrek.h"
#include "boolean.h"
#include "tree.h"
#include "mesinkar.h"
#include <stdlib.h>
#include <stdio.h>

/* *** Konstruktor *** */
void BuildTree(BinTree P)
/* Membentuk sebuah pohon biner P dari pita karakter yang dibaca */
/* I.S. Pita berisi "konstanta" pohon dalam bentuk prefix. Memori pasti cukup, alokasi pasti  berhasil. */
/* F.S. P dibentuk dari ekspresi dalam  pita */
{
	//Kamus Lokal
	char Recipe[256];
	int i;
	//Algoritma
	ADV();
	if (CC==')')
		(*P)=Nil;
	else {
		AlokNode(P);
		for (i=0; i<256; i++)
			Num[i] = 0;
		i = 0;
		while ((CC !='(')&&(CC != ')')) {
			Recipe[i] = CC;
			ADV();
			i++;
		}
    Recipe[i] = '\0';
		Akar(*P) = Recipe;
		BuildTree(&Left(*P));
		BuildTree(&Right(*P));
	}
	ADV();
}
/* Manajemen Memory */
addrNode AlokNode(infotype X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  addrNode P;

  P = (addrNode)malloc(sizeof(infotype));
  if (P != Nil){
    Akar(P) = X;
    Right(P) = Nil;
    Left(P) = Nil;
  }
  return P;
}
void DealokNode(addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
  free(P);
}
/* *** Predikat-Predikat Penting *** */
/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
  return (P == Nil);
}
boolean IsTreeOneElmt(BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
  if (!IsTreeEmpty(P)){
    return ((Left(P) == Nil) && Right(P) == Nil);
  }
}
boolean IsUnerLeft(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
  return ((Right(P) == Nil) && (Left(P) != Nil));
}
boolean IsUnerRight(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
  return ((Right(P) != Nil) && (Left(P) == Nil));
}

void PrintTree(BinTree P, int h)
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
{
  //Not Yet
}

/* *** Searching *** */
boolean SearchTree(BinTree P, infotype X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
  if (P == Nil){
    return false;
  } else {
    if (X == Akar(P)){
      return true;
    } else {
      return (Search(Left(P),X) || Search(Right(P),X));
    }
  }
}
/* *** Fungsi-Fungsi Lain *** */
int Level(BinTree P, infotype X)
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P. 
   Akar(P) level-nya adalah 1. Pohon P tidak kosong. */
{
  //Kamus Lokal
	
	//Algoritma
	if (X==Akar(P)){
		return 1;
	}
	else 
		if (SearchPB(Left(P), X)) {
			return 1+Level(Left(P), X);
		}
		else {
			return 1+Level(Right(P), X);
		}
}