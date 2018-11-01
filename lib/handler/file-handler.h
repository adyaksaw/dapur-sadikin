/* File : file-handler.h */
/* Dapur SADIKIN Game External All File Handler */

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#define REF_FILE1_DIR "~dir/file1.txt"
#define REF_FILE2_DIR "~dir/file2.txt"
#define REF_FILE3_DIR "~dir/file3.txt"

#define MAP_REF_DIR "~dir/map.txt"
#define SAVE_MAP_DIR "~savedir/map.txt"

/* Semuanya masih bisa diubah sesuai kebutuhan */

void LoadMap();
/*
    Prosedur ini akan melakukan load dari file eksternal yang berisi objek-objek dan koordinatnya.
    Parameter masih belum jelas.
*/

void LoadGameStatus();

void LoadMapStatus();

#endif
