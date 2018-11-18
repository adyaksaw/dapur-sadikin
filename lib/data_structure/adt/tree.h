/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */
/* Penamaan type TreeType, type addrNode, dan beberapa fungsi disesuikan 
   karena melibatkan modul list rekursif. */

#ifndef _BINTREE_H_
#define _BINTREE_H_

/* Modul lain yang digunakan : */
#include "listrek.h"
#include "boolean.h"
#include "tree.h"
#include "mesinkar.h"
#include <stdlib.h>
#include <stdio.h>

/* #define Nil NULL */ /* konstanta Nil sesuai pada modul listrek */

/* *** Definisi Type Pohon Biner *** */
typedef char TreeType[20]; 
typedef struct tNode *addrNode;
typedef struct tNode
{
  TreeType info;
  addrNode left;
  addrNode right;
} Node;

/* Definisi PohonBiner : */
/* Pohon Biner kosong : P = Nil */
typedef addrNode BinTree;

/* *** PROTOTYPE *** */

/* *** Selektor *** */
#define Akar(P) (P)->info
#define Left(P) (P)->left
#define Right(P) (P)->right

void BuildTree(Bintree P);
/* Membentuk sebuah pohon biner P dari pita karakter yang dibaca */
/* I.S. Pita berisi "konstanta" pohon dalam bentuk prefix. Memori pasti cukup, alokasi pasti  berhasil. */
/* F.S. P dibentuk dari ekspresi dalam  pita */
/* Manajemen Memory */

addrNode AlokNode(TreeType X);
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DealokNode(addrNode P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */

/* *** Predikat-Predikat Penting *** */

boolean IsTreeEmpty(BinTree P);
/* Mengirimkan true jika P adalah pohon biner kosong */

boolean IsTreeOneElmt(BinTree P);
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */

boolean IsUnerLeft(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */

boolean IsUnerRight(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/

void PrintTree(BinTree P, int h);
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

/* *** Searching *** */
boolean SearchTree(BinTree P, TreeType X);
/* Mengirimkan true jika ada node dari P yang bernilai X */

/* *** Fungsi-Fungsi Lain *** */
int Level(BinTree P, TreeType X);
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P. 
   Akar(P) level-nya adalah 1. Pohon P tidak kosong. */

#endif