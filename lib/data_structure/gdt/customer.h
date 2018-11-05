#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>

#include "../data_type.h"

#include "../adt/point.h"

typedef struct {
  SmallNum amount;
  SmallNum orderID;
  Point tableNum;
  SmallNum patience;
  SmallNum star;
  enum {
    QUEUE = 1,
    SEATED = 2
  } stat;
} Customer;

/* *** Customer *** */
#define Amount(C)       (C).amount
#define FoodOrderID(C)  (C).orderID
#define TableNumber(C)  (C).tableNum
#define Patience(C)     (C).patience
#define Priority(C)     (C).star
#define Status(C)       (C).stat

#endif
