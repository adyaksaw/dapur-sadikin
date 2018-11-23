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

/* *** Konstruktor *** */
BinTree Tree(TypeTree Akar, BinTree L, BinTree R)
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
{
  /*Kamus Lokal*/
  addrNode P = (addrNode) malloc(sizeof(addrNode));
  /*Algoritma*/
  if (P != Nil){
      Akar(P) = Akar;
      Left(P) = L;
      Right(P) = R;
  }
  return P;
}
void MakeTree(TypeTree Akar, BinTree L, BinTree R, BinTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R 
		jika alokasi berhasil. P = Nil jika alokasi gagal. */
{
  /*Kamus Lokal */
  *P = Tree(Akar,L,R);
}

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

boolean IsBiner(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
  if (IsTreeEmpty(P)){
    return false;
  } else {
    return ((Left(P) != Nil) && (Right(P) != Nil));
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
      printf("%s\n", ItemName(Akar(P)));
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
boolean SearchTree(BinTree P, TypeTree X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
  if (IsTreeEmpty(P)){
    return false;
  } else {
    if ((ItemName(X) == ItemName(Akar(P))) && (ItemID(X) == ItemID(Akar(P)))){
      return true;
    } else {
      return (SearchTree(Left(P),X) || SearchTree(Right(P),X));
    }
  }
}

/* *** Fungsi-Fungsi Lain *** */
int NbElmt(BinTree P)
/* Mengirimkan banyaknya elemen (node) pohon biner P */
{
  if (IsTreeEmpty(P)){
    return 0;
  } else {
    return (1 + NbElmt(Left(P)) + NbElmt(Right(P)));
  }
}
int NbDaun(BinTree P)
/* Mengirimkan banyaknya daun (node) pohon biner P */
/* Prekondisi: P tidak kosong */
{
  if (IsTreeEmpty(P)){
    return 0;
  } else if (IsTreeOneElmt(P)){
    return 1;
  } else {
    return (NbDaun(Left(P)) + NbDaun(Right(P)));
  }
}
boolean IsSkewLeft(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kiri */
/* Pohon kosong adalah pohon condong kiri */
{
	/*Kamus Lokal*/
	
	/*Algortima*/
	if (IsTreeEmpty(P)){
		return true;
	} else {
		if (IsTreeOneElmt(P)) {
			return true;
		} else if (IsUnerLeft(P)) {
				return IsSkewLeft(Left(P));
		} else {
				return false;
		}
	}
}
boolean IsSkewRight(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kanan */
/* Pohon kosong adalah pohon condong kanan */
{
	/*Kamus Lokal*/
	
	/*Algortima*/
	if (IsTreeEmpty(P)){
		return true;
	} else {
		if (IsTreeOneElmt(P)) {
			return true;
		} else if (IsUnerRight(P)) {
				return IsSkewRight(Right(P));
		} else {
				return false;
		}
	}
}
int Level(BinTree P, TypeTree X)
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P. 
   Akar(P) level-nya adalah 1. Pohon P tidak kosong. */
{
  /*Kamus Lokal*/
	
	/*Algortima*/
	if ((ItemName(X) == ItemName(Akar(P)) && (X.id == Akar(P).id))){
		return 1;
	}
	else 
		if (SearchTree(Left(P), X)) {
			return 1+Level(Left(P), X);
		}
		else {
			return 1+Level(Right(P), X);
		}
}
int Tinggi(BinTree P)
/* Pohon Biner mungkin kosong. Tinggi pohon kosong = 0.
   Mengirim "height" yaitu tinggi dari pohon */
{
  if (IsTreeEmpty(P)){
    return 0;
  } else {
    if (Tinggi(Left(P)) > Tinggi(Right(P))){
      return 1 + Tinggi(Left(P));
    } else {
      return 1 + Tinggi(Right(P));
    }
  }
}
/* *** Operasi lain *** */
void AddDaunTerkiri(BinTree *P, TypeTree X)
/* I.S. P boleh kosong */
/* F.S. P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
{
	/*Kamus Lokal*/

	/*Algortima*/
	if (IsTreeEmpty(*P)) {
		*P = AlokNode(X);
	} else {
		if (IsTreeEmpty(Left(*P))) {
			Left(*P) = AlokNode(X);
		}
		else {
			AddDaunTerkiri(&Left(*P), X);
		}
	}
}
void AddDaun(BinTree *P, TypeTree X, TypeTree Y, boolean Kiri)
/* I.S. P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau 
        sebagai anak Kanan X (jika Kiri = false) */
/*		Jika ada > 1 daun bernilai X, diambil daun yang paling kiri */
{
	/*Kamus Lokal*/

	/*Algortima*/
	if (IsTreeOneElmt(*P)) {
		if (Kiri) {
			Left(*P) = AlokNode(Y);
		} else {
			Right(*P) = AlokNode(Y);
		}
	} else {
    if (IsUnerLeft(*P)){
      AddDaun(&Left(*P),X,Y,Kiri);
    } else if (IsUnerRight(*P)){
      AddDaun(&Right(*P),X,Y,Kiri);
    } else {
      if (SearchTree(Left(*P), X)) {
        AddDaun(&Left(*P),X,Y,Kiri);
      } else {
        AddDaun(&Right(*P),X,Y,Kiri);
      }
    }
	}
}
/* *** Binary  Search  Tree  *** */
boolean BSearch(BinTree P, TypeTree X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
  if (IsTreeEmpty(P)){
    return false;
  } else {
    if (X.id < Akar(P).id){
      return BSearch(Left(P),X);
    } else if (X.id == Akar(P).id){
      return true;
    } else {
      return BSearch(Right(P),X);
    }
  }
}
void InsSearch(BinTree *P, TypeTree X)
/* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan simpul X. Belum ada simpul P yang bernilai X. */
{
  if (IsTreeEmpty(*P)){
    MakeTree(X,Nil,Nil,P);
  } else {
    if (X.id < Akar(*P).id){
      InsSearch(&Left(*P),X);
    } else {
      InsSearch(&Right(*P),X);
    }
  }
}

void DelBtree(BinTree *P, TypeTree X)
/* I.S. Pohon P tidak  kosong */
/* F.S. Nilai X yang dihapus pasti ada */
/* Sebuah node dengan nilai X dihapus */
{
  /*Fungsi Lokal*/
  void DelNode(BinTree *P){
    /*Kamus Lokal*/
    addrNode q;
    /*Algortima*/
    if (Right(*P)!=Nil) {
      DelNode(&Right(*P));
    }
    else {
      Akar(q) = Akar(*P);
      q = *P;
      *P = Left(*P);
    }
  }
  if (X.id < Akar(*P).id){
    DelBtree(&Left(*P),X);
  } else if(X.id > Akar(*P).id){
    DelBtree(&Right(*P),X);
  } else {
    /*Kamus Lokal*/
    BinTree q;
    q = *P;
    if (IsTreeOneElmt(q)){
      *P = Nil;
    } else if (IsUnerLeft(q)){
      *P = Left(q);
    } else if (IsUnerRight(q)){
      *P = Right(q);
    } else{ //IsBiner
      DelNode(&Left(q));
    }
    DealokNode(q);
  }
}