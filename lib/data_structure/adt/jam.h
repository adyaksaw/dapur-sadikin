/* File: jam.h */
/* Definisi ADT JAM */

#ifndef JAM_H
#define JAM_H

#include "boolean.h"

typedef int Second;

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK TULIS                                     			     */
/* ***************************************************************** */
void TulisSecond (Second S);
/* Menuliskan Second */

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean SEQ (Second S1, Second S2);
/* Mengirimkan true jika S1=S2, false jika tidak */
boolean SNEQ (Second S1, Second S2);
/* Mengirimkan true jika S1 tidak sama dengan S2 */
boolean SLT (Second S1, Second S2);
/* Mengirimkan true jika S1<S2, false jika tidak */
boolean SGT (Second S1, Second S2);
/* Mengirimkan true jika S1>S2, false jika tidak */

/* *** Operator aritmatika JAM *** */
Second NextSecond (Second S);
/* Mengirim 1 detik setelah Second */
Second NextNSecond (Second S, int N);
/* Mengirim N detik setelah Second */
Second PrevSecond (Second S);
/* Mengirim 1 detik sebelum Second */
Second PrevNSecond (Second S, int N);
/* Mengirim N detik sebelum Second */

/* *** Kelompok Operator Aritmetika *** */
int Durasi (Second SAw, Second SAkh);

/* Yang Dipakai */
void SetTime (Second *S, int SS);

void UpdateTime(Second *S);

#endif
