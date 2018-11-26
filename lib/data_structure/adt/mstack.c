#include "stack.h"

int main(){
	Stack X;
	int i;
	Item it;
	CreateEmpty_Stack(&X);
	printf("Empty stack? %d\n", IsEmpty_Stack(X));
	printf("Full stack? %d\n", IsFull_Stack(X));
	isiKata(&(it.name), "Nasi", 4);
	it.id = 10;
	for(i = 1; i <= 4; i++)Push_Stack(&X, it);
	PrintData_Stack(X,1);
	Pop_Stack(&X, &it);
	PrintData_Stack(X,1);
}