#include "../handler/file-handler.c"

int main () {
  int i,j;

  Matrix M1,M2,M3,M4; // deklarasi matrix

  LoadMap(&M1,&M2,&M3,&M4); // load MAP
  Print_Room(M1);
  printf("\n");
  Print_Room(M2);
  printf("\n");
  Print_Room(M3);
  printf("\n");
  Print_Kitchen(M4);
  printf("\n");

  //printf("%d",IsKataSama(CKata,Kata1));

  printf("Di bawah ini adalah TAG!\n");

  for (i = MIN_ROW_MAP ; i <= NRowEff(M2) ; ++i) {
    for (j= MIN_COL_MAP ; j <= NColEff(M2) ; ++j ) {
      printf("%d",(ElmtMx(M4,i,j).tag) );
      if (j != NColEff(M2))
        printf(" ");
    }
    printf("\n");
  }
  return 0;
}
