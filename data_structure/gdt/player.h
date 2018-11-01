/* *** Player *** */
#define Name(P)   (P).name
#define Money(P)  (P).money
#define Life(P)   (P).life
#define Hand(P)   (P).hand
#define Food(P)   (P).food

typedef struct {
  string name;            // refer to 'data_structure/string.h'
  Point pos;
  long money;
  unsigned short life;
  TabInt hand;          // refer to 'data_structure/arraystr.h'
  Stack food;           // refer to 'data_structure/stackt.h'
} Player;

void Load_Player (player * player, file * fplayer);

void Move_Player (Matrix * M, player * player, Point P0, Point P1);