#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>

#include "../adt/boolean.h"

#include "../data_type.h"

#include "customer.h"

typedef enum {
  EMPTY,
  TABLE,
  STOVE,
  TRAY
} GameObj;

typedef struct {
  //unsigned short tag;
  GameObj tag;

  union {
    /* *** Table *** */
    struct {
      SmallNum num;
      SmallNum size;
      boolean isOccupied;
      Customer* customer_here;
    } table;

    /* *** Stove *** */
    struct {
      SmallNum itemID;
    } stove;

  } data;

} Object;

/* *** GAME OBJECTS *** */
#define Tag(O)   (O).tag

/* *** Table *** */
#define TableNumber(O)  (O).data.table.num
#define CapacityOf(O)   (O).data.table.size
#define IsOccupied(O)   (O).data.table.isOccupied
#define OrdersAt(O)     (CustomerAt(O).orderID)
#define CustomerAt(O)   (*((O).data.table.customer_here))

/* *** Stove *** */
#define ItemsIn(O) (O).data.stove.item

#endif
