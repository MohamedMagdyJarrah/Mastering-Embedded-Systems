#include <stdlib.h>
#include <stdio.h>


void checkNumPalindrome(int num)
{
	int reversedNum =0 , temp = num;
	while(num != 0)
	{
		reversedNum = reversedNum + (num%10);
		num /= 10;
		reversedNum *= 10;
	}
	reversedNum /= 10;

	(reversedNum == temp) ? printf("%d is palindrome number",temp) : printf("%d isn't palindrome number",temp);
}

int main()
{
	int num;
	printf("enter num:");
	fflush(stdout);
	scanf("%d",&num);
	checkNumPalindrome(num);
	return 0;
}