/* File: jam.c */
/* Implementasi ADT JAM */

#include "boolean.h"
#include "jam.h"
#include <stdio.h>


/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK TULIS                                      	          	 */
/* ***************************************************************** */
void TulisSecond (Second S)
{
	printf("Waktu Sekarang adalah : %d\n",S);
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean SEQ (Second S1, Second S2)
{
	return (S1==S2);
}

boolean SNEQ (Second S1, Second S2)
{
	return (S1!=S2);
}

boolean SLT (Second S1, Second S2)
{
	return (S1<S2);
}

boolean SGT (Second S1, Second S2)
{
	return (S1>S2);
}

/* *** Operator aritmatika JAM *** */
Second NextSecond (Second S)
{
	return (S+1);
}

Second NextNSecond (Second S, int N)
{
	return (S+N);
}

Second PrevSecond (Second S)
{
	return (S-1);
}

Second PrevNSecond (Second S, int N)
{
	return (S-N);
}


/* *** Kelompok Operator Aritmetika *** */
int Durasi (Second SAw, Second SAkh)
{
	return (SAkh-SAw);
}

/* Yang Dipakai */
void SetTime (Second *S, int SS)
{
	*S = SS;
}

void UpdateTime(Second *S)
{
	*S = NextSecond(*S);
}
