/* File : file-handler.c */
/* Dapur SADIKIN Game External  File Handler */

#include "file-handler.h"
#include <string.h>



void LoadRoom (Matrix *M, int TableNum1 , int TableNum2 , int TableNum3, int TableNum4 ) {
  Kata Kata1, Kata2, Kata3, Kata4;
  int i = MIN_ROW_MAP;
  int j;
  IntToKata(TableNum1,&Kata1);
  IntToKata(TableNum2,&Kata2);
  IntToKata(TableNum3,&Kata3);
  IntToKata(TableNum4,&Kata4);


    while (CC != BARRIER) {
      ADV();
      ADVKATA();

      j = MIN_COL_MAP;
      while ((CC != BREAKLINE) && (CC != BARRIER)) {
          MakeEmptyCustomer(((ElmtMx(*M,i,j)).data.table.customer_here));
          /* Dengan mesin kata mengecek apakah CKata pada file sama dengan table number */
          if (IsKataSama(CKata,Kata1)) {
            ElmtMx(*M,i,j).tag = TABLE;
            TableNumber(ElmtMx(*M,i,j)) = TableNum1;
            CapacityOf(ElmtMx(*M,i,j)) = 4;

          } else if (IsKataSama(CKata,Kata2)) {
            ElmtMx(*M,i,j).tag = TABLE;
            ElmtMx(*M,i,j).data.table.num = TableNum2;
            ElmtMx(*M,i,j).data.table.size = 2;

          } else if (IsKataSama(CKata,Kata3)) {
            ElmtMx(*M,i,j).tag = TABLE;
            ElmtMx(*M,i,j).data.table.num = TableNum3;
            ElmtMx(*M,i,j).data.table.size = 4;

          } else if (IsKataSama(CKata,Kata4)) {
            ElmtMx(*M,i,j).tag = TABLE;
            ElmtMx(*M,i,j).data.table.num = TableNum4;
            ElmtMx(*M,i,j).data.table.size = 2;

          } else {
            /* Tidak melakukan apa apa di M1 */
          }

        if (CC == SECTION)
          ADV();
        else
          ADVKATA();

      ++j;

    }

    ++i;
   }

}

void LoadKitchen (Matrix *M) {
  Kata Kata1, Kata2;
  int i = MIN_ROW_MAP;
  int j;
  int CountItem = 1;

  Kata1.TabKata[1] = 'M'; //KOMPOR, secara fungsionalitas seperti laci.
  Kata1.Length = 1;
  Kata2.TabKata[1] = 'T'; //KOMPOR BENERAN / NAMPAN
  Kata2.Length = 1;

  while (CC != BARRIER) {

    ADV();
    ADVKATA();
    j = MIN_COL_MAP;
    while ((CC != BREAKLINE) && (CC != BARRIER)) {

        if (IsKataSama(CKata,Kata1)) {
          ElmtMx(*M,i,j).tag = STOVE;
          ElmtMx(*M,i,j).data.stove.itemID = CountItem;
          //printf("Elemen ke %d, %d adalah %d\n",i,j,ElmtMx(*M,i,j).tag );
          //printf("ItemID : %d\n",ElmtMx(*M,i,j).data.stove.itemID);
          CountItem++;
          //MakeEmpty_Table (M1,i,j);
        } else if (IsKataSama(CKata,Kata2)) {
          ElmtMx(*M,i,j).tag = TRAY;

        } else {

          /* Tidak melakukan apa apa di M1 */
        }
        if (CC == SECTION)
          ADV();
        else
          ADVKATA();
    ++j;
  }

  ++i;
 }
}

void LoadMap(Matrix *M1, Matrix *M2, Matrix *M3, Matrix *M4)
/*
    Prosedur ini akan melakukan load dari file eksternal yang berisi objek-objek dan koordinatnya.
    Parameter masih belum jelas. */
{
    Kata Kata1, Kata2, Kata3, Kata4;
    MakeEmpty_Map(8,8,M1,1);
    MakeEmpty_Map(8,8,M2,2);
    MakeEmpty_Map(8,8,M3,3);
    MakeEmpty_Map(8,8,M4,4);

    STARTKATA();

    /* Cek apakah line pertama yang dibaca adalah Map atau bukan */
    Kata1.TabKata[1] = 'M';
    Kata1.TabKata[2] = 'a';
    Kata1.TabKata[3] = 'p';
    Kata1.Length = 3;

      if (IsKataSama(CKata,Kata1)) {
    	  ADV();
        ADVKATA();

        isiKata(&Kata1, "1", 1);
        if (IsKataSama(CKata,Kata1)) {
            LoadRoom(M1,1,2,3,4); /*Load Room 1*/
        }


        ADV();
        ADVKATA();

        Kata1.TabKata[1] = '2';
        Kata1.Length = 1;
        if (IsKataSama(CKata,Kata1)) {
          LoadRoom(M2,5,7,6,8); /*Load Room 2*/
        }
        ADV();
        ADVKATA();

        Kata1.TabKata[1] = '3';
        Kata1.Length = 1;
        if (IsKataSama(CKata,Kata1)) {
          LoadRoom(M3,9,11,10,12); /*Load Room 3*/
        }
        ADV();
        ADVKATA();

        Kata1.TabKata[1] = '4';
        Kata1.Length = 1;
        if (IsKataSama(CKata,Kata1)) {
          LoadKitchen(M4); /*Load Room 4*/

        }
        ADV(); /*ADVANCE */
      }
  }
