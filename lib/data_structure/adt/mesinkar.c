/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkar.h"
#include <stdio.h>
#include <errno.h>

char CC;
boolean EOP;

static FILE * pita;
static int retval;

void START() {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	pita = fopen(NamaFile,"r");
	if (pita == NULL) {
		printf("Error %d \n",errno);
	} else {
		ADV();
	}
}

void ADV() {
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
		  Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */

	retval = fscanf(pita,"%c",&CC);

	//printf("CC isinya ini lho : %c\n",CC);
	EOP = (CC == MARK);
	if (EOP) {
			printf("FILE AKAN DITUTUP\n");
       fclose(pita);
 	}

}
