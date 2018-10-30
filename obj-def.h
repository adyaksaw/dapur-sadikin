/* File : obj-def.h */
/* Dapur SADIKIN Game Object Definition */

#ifndef OBJ_DEF_H
#define OBJ_DEF_H

#include "data_structure/string.h"
#include "data_structure/point.h"
#include "data_structure/ref_array.h"
#include "data_structure/stack.h"
#include "data_structure/matrix.h"

/* ********** OBJECT DEFINITION ********** */
typedef struct {
  string name;            // refer to 'data_structure/string.h'
  Point pos;
  long money;
  unsigned short life;
  TabRef hand;           // refer to 'data_structure/arraystr.h'
  Stack food;          // refer to 'data_structure/stackt.h'
} player, *player_ptr;

typedef struct {
  unsigned short num;
  IdType orderId;
  Point tableNum;
  short fuse;
  unsigned short star;
  //unsigned short stat;
  enum {
    QUEUE = 1,
    SEATED = 2
  } stat;
} customer, *customer_ptr;

typedef struct {
  //unsigned short tag;
  gameObj tag;

  union {
    /* *** Table *** */
    struct {
      unsigned short num;
      unsigned short size;
      boolean isFull;
      customer_ptr who;
    } table;

    /* *** Stove *** */
    struct {
      IdType itemId;
    } stove;

  } data;

} obj, *obj_ptr;

/* ********** OBJECT SELECTOR ********** */
/* *** Player *** */
#define Name(P)   (P).name
#define Money(P)  (P).money
#define Life(P)   (P).life
#define Hand(P)   (P).hand
#define Food(P)   (P).food

/* *** Customer *** */
#define Number(C)     (C).num
#define Patience(C)   (C).fuse
#define Priority(C)   (C).star
#define Status(C)     (C).stat

/* *** GAME OBJECTS *** */
#define Tag(O)   (O).tag
  /* *** Table *** */
  #define CapacityOf(O)   (O).size
  #define IsOccupied(O)   (O).isFull
  #define OrdersAt(O)     (O).order
  #define CustomerAt(O)   (*((O).who))

  /* *** Stove *** */
  #define ItemsIn(O) (O).item


/* ********** OBJECT CONSTRUCTOR ********** */

#endif
