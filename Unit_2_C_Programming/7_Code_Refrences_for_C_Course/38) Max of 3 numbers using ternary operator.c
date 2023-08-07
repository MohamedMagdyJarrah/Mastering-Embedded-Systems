#include <stdlib.h>
#include <stdio.h>

int Max3NumsUsingTernaryOp(int a,int b,int c)
{
	return a>b?(a>c?a:c):(b>c?b:c);
}

int main()
{
	int a,b,c,max;
	printf("enter three numbers:");
	fflush(stdout);
	scanf("%d %d %d",&a,&b,&c);
	max=Max3NumsUsingTernaryOp(a,b,c);
	printf("max is %d",max);
	return 0;

}