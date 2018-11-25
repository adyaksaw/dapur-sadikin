/* File : stack.h */
/* Stack of Items */
/* Deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include "stack.h"
/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty_Stack (Stack *S){
	/* I.S. sembarang; */
	/* F.S. Membuat sebuah stack S yang kosong berkapasitas MAX_ELMT_STACK_STR */
	/* jadi indeksnya antara 1.. MAX_ELMT_STACK_STR+1 karena 0 tidak dipakai */
	/* Ciri stack kosong : TOP bernilai NULL_STACK_STR */
	Top(*S) = NULL_STACK_STR;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty_Stack (Stack S){
	/* Mengirim true jika Stack kosong: lihat definisi di atas */
	return (Top(S) == NULL_STACK_STR);
}

boolean IsFull_Stack (Stack S){
	/* Mengirim true jika tabel penampung nilai elemen stack penuh */
	return (Top(S) == MAX_ELMT_STACK_STR);
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push_Stack (Stack * S, infotype_food newEl){
	/* Menambahkan str sebagai infotype_food baru pada Stack S. */
	/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
	/* F.S. str menjadi name TOP yang baru, ready bernilai false, TOP bertambah 1 */
	if(IsEmpty_Stack(*S))Top(*S) = 1;
	else Top(*S)++;
	InfoTop(*S) = newEl;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop_Stack (Stack * S, infotype_food * X){
	/* Menghapus X dari Stack S. */
	/* I.S. S  tidak mungkin kosong */
	/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
	*X = InfoTop(*S);
	Top(*S)--;
}

/* ********** KELOMPOK BACA/TULIS ********** */
void Input_Stack (Stack * S, FILE * fptr){
	/* Membaca Stack S dari FILE teks eksternal. */
	/* I.S. S sembarang */
	/* F.S. Save FILE fptr masuk ke Stack S */
	infotype_food F;

	CreateEmpty_Stack(S);
	fscanf(fptr, "%s", &ItemName(F));
	while (ItemName(F) != "ES"){
		fscanf(fptr, "%d", &ItemID(F));
		Push_Stack(S,F);
		fscanf(fptr, "%s", &ItemName(F));
	}
}

void Save_Stack (Stack * S, FILE * fptr){
	/* Menyimpan Stack S ke FILE teks eksternal. */
	/* I.S. S terdefinisi */
	/* F.S. Stack S terdefinisi ke FILE fptr */
	Stack Temp;
	infotype_food T;

	CreateEmpty_Stack(&Temp);
	while (!IsEmpty_Stack(*S)){
		Pop_Stack(S,&T);
		Push_Stack(&Temp,T);
	}
	while (!IsEmpty_Stack(Temp)){
		Pop_Stack(&Temp,&T);
		Push_Stack(S,T);
		fprintf(fptr,"%s %d",ItemName(T),ItemID(T));
		//fprintf(fptr,ItemName(T));
	}
}

void PrintData_Stack (Stack S, boolean isHand){
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
	int i;
	if(IsEmpty_Stack(S)){
		if(isHand){
			printf("Anda tidak memegang apapun\n");
		} else {
			printf("Nampan anda kosong.\n");
		}
	} else {
		for(i = 1; i <= Top(S); i++){
			printf("[%d]", i);
			printKata(S.T[i].name);
			printf("\n");
		}
	}
}

//Fungsi Lain
Stack Reverse_Stack(Stack *S){
	Stack Temp1, Temp2;
	infotype_food T;

	CreateEmpty_Stack(&Temp1);
	CreateEmpty_Stack(&Temp2);
	//Make 2 Reversed Version of Stack Input,
	//1 for return
	//2 for normalize Stack Input
	while (!IsEmpty_Stack(*S)){
		Pop_Stack(S,&T);
		Push_Stack(&Temp1,T);
		Push_Stack(&Temp2,T);
	}
	//Normalize Stack Input
	while (!IsEmpty_Stack(Temp1)){
		Pop_Stack(&Temp1,&T);
		Push_Stack(S,T);
	}
	return Temp2;
}