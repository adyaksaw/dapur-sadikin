#include <stdlib.h>
#include <stdio.h>

#include "static-obj.h"

boolean PlaceCustomerToTable(Object * Table, Customer * Cust){
  if (CapacityOf(*Table) >= Amount(*Cust) && !(*Table).data.table.isOccupied){
    (*Table).data.table.customer_here = Cust;
    (*Table).data.table.isOccupied = true;
    printf("Pelanggan telah ditaruh di meja nomor %d.\n", TableNumber(*Table));
    return true;
  }else {
    return false;
  }
}

boolean findValidCust(Object * Table, Queue * Q){
  int i;
  boolean isFound;
  isFound = false;
  for(i = Head(*Q); i != Tail(*Q) && !isFound; i = 1+(i%MaxEl(*Q))){
    Customer * Cust = (*Q).T[i];
    if(CapacityOf(*Table) >= Amount(*Cust)){
      (*Table).data.table.customer_here = Cust;
      (*Table).data.table.isOccupied = true;
      printf("Pelanggan telah ditaruh di meja nomor %d.\n", TableNumber(*Table));
      normalizedQueue(Q, i);
      isFound = true;
    }
  }
  Customer * Cust = InfoTail(*Q);
  if(CapacityOf(*Table) >= Amount(*Cust)){
    (*Table).data.table.customer_here = Cust;
    (*Table).data.table.isOccupied = true;
    printf("Pelanggan telah ditaruh di meja nomor %d.\n", TableNumber(*Table));
    normalizedQueue(Q, Tail(*Q));
    isFound = true;
  }
  return isFound;
}

void RemoveCustomerFromTable(Object * Table){
	if(!(*Table).data.table.isOccupied){
		printf("Tidak ada customer pada table nomor %d!\n", TableNumber(*Table));
	} else {
		Dealokasi_Customer((*Table).data.table.customer_here);
		(*Table).data.table.isOccupied = false;
	}
}