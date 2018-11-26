//Driver table
#include "boolean.h"
#include "stdio.h"
#include "table.h"


int main(){
	Table T;
	Item it;
	
	MakeEmpty_Table(&T);
	printf("Empty table? %d\n", IsEmpty_Table(T));
	printf("Full table? %d\n", IsFull_Table(T));
	isiKata(&(it.name), "Nasi", 4);
	it.id = 10;
	isiKata(&(it.name), "Nasi", 4);
	it.id = 10;
}
