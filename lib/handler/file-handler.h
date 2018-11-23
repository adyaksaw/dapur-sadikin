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

/* Semuanya masih bisa diubah sesuai kebutuhan */

void LoadMap(Matrix *M1, Matrix *M2, Matrix *M3, Matrix *M4);
/*
    Prosedur ini akan melakukan load dari file eksternal yang berisi objek-objek dan koordinatnya.
    Parameter masih belum jelas.
*/

void LoadGameStatus();

void LoadMapStatus();

void LoadMapSave();

void Save();

#endif
