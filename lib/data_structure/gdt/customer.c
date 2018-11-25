#include <stdlib.h>
#include <stdio.h>

#include "customer.h"

void MakeEmptyCustomer (Customer *Cust) {
  Cust = NULL;
}

Customer * GenerateCustomer(){
  Customer * newCustomer = malloc(sizeof(Customer));
  Amount(*newCustomer) = 1 + (rand() % 4);
  FoodOrderID(*newCustomer) = 0;
  TableNum(*newCustomer) = 0;
  Priority(*newCustomer) = rand() % 2;
  if (Priority(*newCustomer) == 0){
    Patience(*newCustomer) = 30;
  }else if (Priority(*newCustomer) == 1){
    Patience(*newCustomer) = 20;
  }
  Status(*newCustomer) = QUEUE;

  return newCustomer;
}

void GenerateOrder(Customer * Cust){
  FoodOrderID(*Cust) = 16+(rand() % FoodNumber);
}

boolean hasOrdered(Customer *Cust){
  return (FoodOrderID(*Cust) != 0);
}

void printCustomer(Customer customer){
  printf("Customer\n");
  printf("%d orang. Meja nomor %d. Kesabaran %d. Prioritas %d. Status %d.\n", Amount(customer), TableNum(customer), Patience(customer), Priority(customer), Status(customer));
}

void Save_Cust(Customer customer, FILE *fp){
  fprintf(fp,"%d %d %d %d %d\n",Amount(customer), TableNum(customer), Patience(customer), Priority(customer), Status(customer));
}

void Load_Cust(Customer *customer, FILE *fp){
  fscanf(fp,"%d %d %d %d %d",&Amount(*customer), &TableNum(*customer), &Patience(*customer), &Priority(*customer), &Status(*customer));
}

void Dealokasi_Customer(Customer *Cust){
  free(Cust);
  printf("FREED\n");
  Cust = NULL;
  if (Cust == NULL){
    printf("FREED\n");
  }
}

void Reduce_Patience(Customer *Cust){
  Patience(*Cust) -= 1;
}