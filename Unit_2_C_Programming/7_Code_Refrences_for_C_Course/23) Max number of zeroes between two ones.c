#include <stdlib.h>
#include <stdio.h>

int maxZeroesBetween2Ones(unsigned long long num)
{
	int maxOnes = 0 , maxCount = 0 , oneDetected = 0 , i;

	for(i=0 ; i< sizeof(num)*8 ; i++)		/* sizeof(num)*8 to get number of bits of the variable*/
	{
		if( ( ((num>>i)&1) == 1) && oneDetected == 0)		/* To check it is the first 1 or not */
		{
			oneDetected = 1;
		}
		else if( (( (num>>i)&1) == 1) && oneDetected == 1)	/* To stop counting zero at the second 1 and check number of zeros*/
		{
			if( maxCount > maxOnes)
			{
				maxOnes = maxCount;
			}
			maxCount = 0;
			oneDetected = 0;		/* oneDetected = 0 and i-- to start count from the new 1 and i-- to start from the same 1 the next loop */
			i--;					/* and don't skip it as i increments in the loop */
			/* ex:101001 we will stop at third 1 from left then i increments (i--) prevent this to start from it as it will be the new start */
		}
		else if( ( ( (num>>i)&1) == 0) && oneDetected == 1 )  /* To check the zero between 1 or not start with one ex:1001 or 1000 */
		{
			maxCount++;
		}
	}

	return maxOnes;
}

int main(void)
{
	printf("max zeros in %d is %d",257,maxZeroesBetween2Ones(257));
	return 0;
}
