
#include<stdio.h>
#include<string.h>
#include<math.h>

int main(void)
{
	int x=500;
	int d = 2;
	x = x / pow(10,3-d); //������ �����Ҷ� 10^3-d����


	printf("%d", x);
	return 0;
}