/* File : file-handler.h */
/* Dapur SADIKIN Game External All File Handler */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#define REF_FILE1_DIR "~dir/file1.txt"
#define REF_FILE2_DIR "~dir/file2.txt"
#define REF_FILE3_DIR "~dir/file3.txt"

#define MAP_REF_DIR "~dir/map.txt"
#define SAVE_MAP_DIR "~savedir/map.txt"

#include "../data_structure/adt/matrix.h"
#include "../data_structure/adt/tree.h"



void LoadRoom (Matrix *M, int TableNum1 , int TableNum2 , int TableNum3, int TableNum4 );
/* I.S. *M sembarang, TableNum1,2,3,4 terdefinisi */
/* F.S. Matriks M diload dengan TableNumbernya dan beberapa hal terkait untuk gameplay, selama dia bukan kitchen */


void LoadMap(Matrix *M1, Matrix *M2, Matrix *M3, Matrix *M4);
/*
    Prosedur ini akan melakukan load dari file eksternal yang berisi objek-objek dan koordinatnya.
    Isinya adalah Map yang berisi room-room dan kitchen.
*/

void LoadKitchen (Matrix *M);

/* I.S. *M sembarang  */
/* F.S. Matriks M diload dengan  M/T nya dan beberapa hal terkait untuk gameplay, M diisi dengan objek pada kitchen */

void LoadMap(Matrix *M1, Matrix *M2, Matrix *M3, Matrix *M4);

/* I.S M1,M2,M3,M4 sembarang */
/* F.S. M1 diisi Room1, M2 diisi Room2, M3 diisi Room3, M4 diisi Kitchen */

#endif
