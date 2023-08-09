#include <stdlib.h>
#include <stdio.h>

void checkFrequencyOfDigits(int num)
{
	unsigned char arr[10] = {0};
	unsigned char digit , i;
	while(num != 0)
	{
		digit = num%10;
		arr[digit]++;
		num/=10;
	}

	for(i=0 ; i<10 ; i++)
	{
		if(arr[i] == 0)
			continue;
		else
		{
			printf("%d occurs %d times\n",i,arr[i]);
		}
	}
}

int main()
{
	int num;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	checkFrequencyOfDigits(num);
	return 0;
}