#include <stdio.h>
#include <stdlib.h>

int ConvertLittleEndianToBig(int num)
{
	int bigEndian = 0 , numSize = sizeof(num) , i;

	for(i=numSize-1;i>=0;i--)
	{
		bigEndian |= (num & 0xff)<<(i*8) ;
		num = num>>8;
	}

	return bigEndian;
}


int main(void) {
	int littleEndian = 0x12345678, bigEndian;
	printf("Little endian = %x\n",littleEndian);
	bigEndian = ConvertLittleEndianToBig(littleEndian);
	printf("Big Endian = %x\n",bigEndian);
	return 0;
}