#include <stdlib.h>
#include <stdio.h>

int MaxNumUsingTernaryOp(int a,int b)
{
	return a>b?a:b;
}

int main()
{
	int a,b,max;
	printf("enter two numbers:");
	fflush(stdout);
	scanf("%d %d",&a,&b);
	max=MaxNumUsingTernaryOp(a,b);
	printf("max is %d",max);
	return 0;

}