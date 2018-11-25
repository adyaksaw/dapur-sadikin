/*
NIM : 13517115
Nama : Edward Alexander Jaya
Tanggal : 05 September 2018
Topik praktikum : ADT Jam dan Point (ADT Point)
Deskripsi : File ini adalah driver untuk mengecek semua function dan void function (prosedur) yang ada pada
point.c.

*/

#include <stdio.h>
#include "point.h"
#include "boolean.h"
int main () {
  Point P1;
  P1 = MakePoint (1.00,2.00);
  printf("%f %f\n",Absis(P1),Ordinat(P1));
  return 0;
}
