#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void reverseArr(int arr[],int arr_count);
void checkUsername(char str[]);
int lastOccurence(int arr[],int arr_count,int num);
int FourthLeastSignificant(int num);
void clearSpecifiedBit(int num,int removedBit);
int checkPowerOf3(int num);



int main(void)
{

	return 0;
}


void reverseArr(int arr[],int arr_count)
{
	int i=0 , j;
	j = arr_count-1;
	for(i=0 ; i<arr_count/2 ; i++)
	{
		arr[i] = arr[i] + arr[j];
		arr[j] = arr[i] - arr[j];
		arr[i] = arr[i] - arr[j];
		j--;
	}
}

void checkUsername(char str[])
{
	char username[10] = "USERNAME";
	if(!strcmp(str,username))
	{
		printf("The same USERNAME");
	}
	else
	{
		printf("Not found");
	}
}

int lastOccurence(int arr[],int arr_count,int num)
{
	int i=0 , index = -1;
	for(i=0;i<arr_count;i++)
	{
		if(arr[i] == num)
		{
			index = i;
		}
	}
	return index;
}

int FourthLeastSignificant(int num)
{
	int fourthBit , bits = 0 , rem=0;
	/*Converting num to binary*/
	while (num != 0)
	{
		rem = num%2;
		num = num/2;
		bits++;
		if(bits == 4)
		{
			fourthBit = rem;
		}
	}

	return fourthBit;
}

void clearSpecifiedBit(int num,int Bit)
{
	int  bitsCount=0 , mainNum = num;
	/*Convert tot binary and save in array*/
	while (num != 0)
	{
		num = num/2;
		bitsCount++;
	}

	if(Bit >= bitsCount)
	{
		printf("%d",mainNum);		/*Print the Same number the removed bit can't be accessable*/
	}
	else
	{
		/*Clearing the bit*/
		mainNum &= ~(1<<Bit);
		printf("%d" , mainNum);
	}
}

int checkPowerOf3(int num)
{
	int prevNum=0;
	while(num != 0)
	{
		prevNum = num;
		num /= 3;
		if((num == 1) && (prevNum%3==0))
		{
			return 0;
		}
	}
	return 1;
}


