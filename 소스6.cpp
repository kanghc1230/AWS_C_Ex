#include<stdio.h>
void swap(int n1, int n2) {		//call by value
	int temp = n1;
	n1 = n2;
	n2 = temp;
	printf("함수 %d %d \n", n1, n2);
}

void swap2(int *n1, int *n2) {		//call by reference
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
	printf("함수 %d %d \n", *n1, *n2);
}

int main(void)
{
	int num1 = 90;
	int num2 = 50;

	printf("call by value \n");

	printf("메인 %d %d \n", num1, num2);

	swap(num1, num2);

	printf("메인 %d %d \n", num1, num2);

	printf("\ncall by reference \n");

	swap2(&num1, &num2);

	printf("메인 %d %d \n", num1, num2);


	return 0;
}