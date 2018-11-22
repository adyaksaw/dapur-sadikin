#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>

#include "../data_type.h"

#include "../adt/point.h"

typedef struct {
  SmallNum amount;
  SmallNum orderID;
  SmallNum tableNum;
  SmallNum patience;
  SmallNum star;
  enum {
    QUEUE = 1,
    SEATED = 2,
    UNDEF = 0
  } stat;
} Customer;

/* *** Customer *** */
#define Amount(C)       (C).amount
#define FoodOrderID(C)  (C).orderID
#define TableNum(C)     (C).tableNum
#define Patience(C)     (C).patience
#define Priority(C)     (C).star
#define Status(C)       (C).stat

#define FoodNumber 8

void MakeEmptyCustomer (Customer *Cust);

Customer * GenerateCustomer();

void GenerateOrder(Customer * Cust);

void printCustomer(Customer customer);

void Dealokasi_Customer(Customer *Cust);

#endif
