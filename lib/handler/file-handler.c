/* File : file-handler.c */
/* Dapur SADIKIN Game External All File Handler */

#include "file-handler.h"
#include <string.h>


/* Semuanya masih bisa diubah sesuai kebutuhan */

void LoadMap(Matrix *M1, Matrix *M2, Matrix *M3, Matrix *M4)
/*
    Prosedur ini akan melakukan load dari file eksternal yang berisi objek-objek dan koordinatnya.
    Parameter masih belum jelas. */
{
      MakeEmpty_Map(8,8,M1);
      MakeEmpty_Map(8,8,M2);
      MakeEmpty_Map(8,8,M3);
      MakeEmpty_Map(8,8,M4);

    	STARTKATA();
      
    	if (strcmp(CKata.TabKata, "Map") == 0) {
    		ADVKATA();

        if (strcmp(CKata.TabKata, "1") == 0) {
          int i = MIN_ROW_MAP;
      		int j;
      			while (CC != BARRIER) {
      				ADVKATA();
      				j = MIN_COL_MAP;
      				while ((CC != BREAKLINE) && (CC != BARRIER)) {
      					if (strcmp(CKata.TabKata, "-") == 0) {
                  /* Tidak melakukan apa-apa karena sudah di CreateEmpty */
                } else {
                  if (strcmp(CKata.TabKata, "1") == 0) {
                    ElmtMx(*M1,i,j).tag = TABLE;
                    TableNumber(ElmtMx(*M1,i,j)) = 1;
                    CapacityOf(ElmtMx(*M1,i,j)) = 4;
                    MakeEmpty_Table (M1,i,j);
                  } else if (strcmp(CKata.TabKata, "2") == 0) {
                    ElmtMx(*M1,i,j).tag = TABLE;
                    ElmtMx(*M1,i,j).data.table.num = 2;
                    ElmtMx(*M1,i,j).data.table.size = 2;
                    MakeEmpty_Table (M1,i,j);
                  } else if (strcmp(CKata.TabKata, "3") == 0) {
                    ElmtMx(*M1,i,j).tag = TABLE;
                    ElmtMx(*M1,i,j).data.table.num = 3;
                    ElmtMx(*M1,i,j).data.table.size = 4;
                    MakeEmpty_Table (M1,i,j);
                  } else if (strcmp(CKata.TabKata, "4") == 0) {
                    ElmtMx(*M1,i,j).tag = TABLE;
                    ElmtMx(*M1,i,j).data.table.num = 4;
                    ElmtMx(*M1,i,j).data.table.size = 2;
                    MakeEmpty_Table (M1,i,j);
                  }
              }
              ADVKATA();
              ++j;
            }
      			++i;
      	}
            ADV(); /*MARK */
      }
    }
  }


void LoadGameStatus() {}

void LoadMapStatus() {}

void LoadMapSave() {}

void Save() {}
