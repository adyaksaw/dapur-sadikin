#include "point.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Point *** */
Point MakePoint (float X, float Y){
	/* Membentuk sebuah Point dari komponen-komponennya */	
	Point P;

	Absis(P) = X;
	Ordinat(P) = Y;

	return P;
}

/* *** Kelompok operasi relasional terhadap Point *** */
boolean EQ (Point P1, Point P2){
	/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
	return((Absis(P1) == Absis(P2)) && ((Ordinat(P1) == (Ordinat(P2)))));
}

boolean NEQ (Point P1, Point P2){
	/* Mengirimkan true jika P1 tidak sama dengan P2 */	
	return !EQ(P1, P2);
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */
float Distance_Point (Point P1, Point P2){
	/* Menghitung panjang garis yang dibentuk P1 dan P2 */
	/* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
	/* Tuliskan spec fungsi yang lebih tepat. */

	float distX, distY;

	distX = Absis(P1) - Absis(P2);
	distX *= distX;

	distY = Ordinat(P1) - Ordinat(P2);
	distY *= distY;

	return(sqrt(distX + distY));
}