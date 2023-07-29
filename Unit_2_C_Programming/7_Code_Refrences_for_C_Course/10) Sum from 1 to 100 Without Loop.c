#include <stdlib.h>
#include <stdio.h>

int Sum1To100WithoutLoop()
{
	static int sum = 0 , i =1;
	if(i !=100)
	{
		sum += i;
		i++;
		Sum1To100WithoutLoop();
	}
	return sum;
}

int main(void)
{
	printf("The sum from 1 to 100 without loop is %d",Sum1To100WithoutLoop());
	return 0;
}
