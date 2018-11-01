#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string.h>

#include "data_structure/adt/point.h"
#include "data_structure/adt/integer_table.h"
#include "data_structure/adt/stack.h"
#include "data_structure/adt/matrix.h"

/* *** Customer *** */
#define Amount(C)       (C).num
#define FoodOrderID(C)  (C).orderID
#define TableNumber(C)  (C).tableNum
#define Patience(C)     (C).patience
#define Priority(C)     (C).star
#define Status(C)       (C).stat

typedef struct {
  unsigned short amount;
  IdType orderID;
  Point tableNum;
  short patience;
  unsigned short star;
  enum {
    QUEUE = 1,
    SEATED = 2
  } stat;
} Customer;

#endif