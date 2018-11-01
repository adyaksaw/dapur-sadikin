/* File : file-controller.h */
/* Dapur SADIKIN Game External File Controller */

#ifndef FILE_CTRL_H
#define FILE_CTRL_H

#include "namespace.h"
#include "string.h"

#define REF_FILE1_DIR "~dir/file1.txt"
#define REF_FILE2_DIR "~dir/file2.txt"
#define REF_FILE3_DIR "~dir/file3.txt"

/* ********** MANAJEMEN DATA ********** */
/* *** Retrieve data *** */
string GetDataVal (TabInt T, ElType X);
/* Retrieve data koresponden dari file eksternal */

/* *** Retrieve identifier *** */
ElType GetDataId (TabInt T, string S);
/* Retrieve integer identifier data dalam file eksternal */

#endif
