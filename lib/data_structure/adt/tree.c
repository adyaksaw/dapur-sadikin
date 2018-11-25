/* Nama : Mohammad Ridwan Hady Arifin */
/* NIM : 13517007 */

/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */
/* Penamaan type infotype, type addrNode, dan beberapa fungsi disesuikan
   karena melibatkan modul list rekursif. */

/* Modul lain yang digunakan : */
#include "listrek.h"
#include "boolean.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "../gdt/game_data_type.h"

/* #define Nil NULL */ /* konstanta Nil sesuai pada modul listrek */

BinTree BuildBalanceTree(int n, FILE *fp)
/* Menghasilkan sebuah balanced tree dengan n node, nilai setiap node dibaca */
{
  /*Kamus Lokal*/
  TypeTree X;
  BinTree P;
  /*Algoritma*/
  if (n==0){
    return Nil;
  } else {
    fscanf(fp, "%d %s", &ItemID(X), ItemName(X));
    normalizeFromFscanf(&(X.name));
    P = AlokNode(X);
    if (P != Nil){
      Left(P) = BuildBalanceTree(n/2, fp);
      Right(P) = BuildBalanceTree(n-(n/2)-1, fp);
    }
    return P;
  }
}
/* Manajemen Memory */
addrNode AlokNode(TypeTree X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  /*Kamus Lokal*/
  addrNode P = (addrNode) malloc(sizeof(Node));

  /*Algoritma*/
  if (P != Nil){
    Akar(P) = X;
    Right(P) = Nil;
    Left(P) = Nil;
    return P;
  } else {
    return Nil;
  }

}
void DealokNode(addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
  /*Kamus Lokal*/

  /*Algortima*/
  free(P);
}
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
  } else {
    return false;
  }
}
/* *** Traversal *** */
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
  /*Prosedur Lokal*/
  void PrintTreeWithIndent(BinTree P, int h, int idt)
  {
    int i;
    if (!IsTreeEmpty(P)){
      printf("%d ",Akar(P).id);
      printKata(Akar(P).name);
      printf("\n");
      if (!IsTreeEmpty(Left(P))){
        for (i=1; i<=h+idt;i++){
          printf(" ");
        }
        PrintTreeWithIndent(Left(P),h, idt+h);
      }
      if (!IsTreeEmpty(Right(P))){
        for (i=1; i<=h+idt;i++){
          printf(" ");
        }
        PrintTreeWithIndent(Right(P),h,idt+h);
      }
    }
  }
  /*Kamus Lokal*/

  /*Algoritma*/
  PrintTreeWithIndent(P,h,0);
}
/* *** Searching *** */


Item SearchItemTree(BinTree P, SmallNum X){
  /* Mengirimkan true jika ada node dari P yang memiliki ItemID X */
  Item notFound;
  ItemID(notFound) = 255;
  if (IsTreeEmpty(P)){
    return notFound;
  } else {
    if (X == ItemID(Akar(P))){
      return Akar(P);
    } else if(ItemID(SearchItemTree(Left(P), X)) != 255){
      return SearchItemTree(Left(P),X);
    } else if(ItemID(SearchItemTree(Right(P),X)) != 255){
      return SearchItemTree(Right(P),X);
    } else return notFound;
  }
}