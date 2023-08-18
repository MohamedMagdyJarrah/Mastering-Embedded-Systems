#include <stdio.h>
#include <stdlib.h>

void find_sizeof_two_dimentional_array_without_sizeof_operator(){
	int a[3][3]={ {1,2,3},{4,5,6},{7,8,9} };
	int *p1=&a[0][0];  //pointer points to the first element in the array
	int (*p2)[3][3]=&a+1; //pointer points to the whole array
	int size=(**p2)-p1;
	printf("%d\n",size);
}


int main(void)
{
	find_sizeof_two_dimentional_array_without_sizeof_operator();
	return 0;
}