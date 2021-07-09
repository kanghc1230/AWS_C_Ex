
#include<stdio.h>
#include<string.h>
#include<math.h>

int main(void)
{
	int x=500;
	int d = 2;
	x = x / pow(10,3-d); //제곱의 연산할때 10^3-d가능


	printf("%d", x);
	return 0;
}