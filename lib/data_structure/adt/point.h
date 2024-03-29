/* File: point.h */
/* *** Definisi ABSTRACT DATA TYPE Point *** */

#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "math.h"

typedef struct {
	float X; /* absis   */
	float Y; /* ordinat */
} Point;

#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint (float X, float Y);
/* Membentuk sebuah Point dari komponen-komponennya */

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQ (Point P1, Point P2);
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
boolean NEQ (Point P1, Point P2);
/* Mengirimkan true jika P1 tidak sama dengan P2 */

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
float Distance_Point (Point P1, Point P2);
/* Menghitung panjang garis yang dibentuk P1 dan P2 */
/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
/* Tuliskan spec fungsi yang lebih tepat. */

#endif
