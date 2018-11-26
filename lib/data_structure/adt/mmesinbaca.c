//Deskripsi		: Menenkripsikan suatu kalimat dengan caesar cipher


#include <stdio.h>
#include "mesinbaca.h"
#include "boolean.h"

int main(){
	int i,t;
	int temp;
	Kata tempKata;
	STARTKATA();
	t = CKata.Length;
	for(i = 1; i <= CKata.Length; i++){
		temp = CKata.TabKata[i]-'A';
		temp += t;
		temp %= 26;
		printf("%c", temp+'A');
	}
	do{
		ADVKATA();
		if(EndKata)break;
		printf(" ");
		printf("Kata1: ");
		printKata(CKata);
		printf("\n");
		printf("KataToInt: %d\n", KataToInt(CKata));
		printf("Kata2: ");
		IntToKata(KataToInt(CKata), &tempKata);
		printKata(tempKata);
		printf("\n");
		printf("IsKataSama: %d\nKata3: ", IsKataSama(tempKata,CKata));
		isiKata(&tempKata, "Wat", 3);
		printKata(tempKata);
		printf("\n");
		for(i = 1; i <= CKata.Length; i++){
			temp = CKata.TabKata[i]-'A';
			temp += t;
			temp %= 26;
			printf("%c", temp+'A');
		}
	}while(!EndKata);
	printf(".\n");
}