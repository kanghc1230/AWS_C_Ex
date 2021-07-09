#include<stdio.h>
int main(void)
{
	int a[] = { 0, 1, 2, 3, 4 };
	int* p[] = { a, a + 1, a + 2, a + 3 ,a + 4 };
	int** pp = p;

	printf("%d %d \n", a, *a);
	printf("%d %d %d \n", p, *p,**p);
	printf("%d %d %d \n\n", pp, *pp, **pp);

	pp++;
	*pp++;
	*++pp;
	++* pp;
	printf("%d %d %d \n", pp - p, *pp - a, **pp);

	pp = p;
	printf("%d \n", *pp++);
	pp = p;
	printf("%d \n", *++pp);

	return 0;
}
