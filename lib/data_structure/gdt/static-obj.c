#include <stdlib.h>
#include <stdio.h>

#include "static-obj.h"

boolean PlaceCustomerToTable(Object * Table, Customer Cust){
  if (CapacityOf(*Table) >= Amount(Cust) && !(*Table).data.table.isOccupied){
    (*Table).data.table.customer_here = &Cust;
    (*Table).data.table.isOccupied = true;
    printf("Pelanggan telah ditaruh di meja nomor %d.\n", TableNumber(*Table));
    return true;
  }else {
    printf("Meja nomor %d tidak muat untuk %d orang!\n", TableNumber(*Table), Amount(Cust));
    return false;
  }
}