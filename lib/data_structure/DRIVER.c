#include "../handler/file-handler.c"

int main () {
  Matrix M1,M2,M3,M4; // deklarasi matrix

  LoadMap(&M1,&M2,&M3,&M4); // load MAP
  Print_Map(M1);
  return 0;
}
