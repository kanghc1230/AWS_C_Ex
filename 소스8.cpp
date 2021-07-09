#include<stdio.h>
//void 포인터 (바구니같음 함수 주소값 다)
//근데 참조,변경=20불가 포인터연산++불가 
//장점 주소값에만 의미를두고 포인터형은 나중에 결정할때, 동적메모리할당할

void sosimplefunc(void)
{
	printf("im so simple");
}

int main(void) 
{
	int num = 20;
	void *ptr = &num;

	printf("%p \n", ptr);

	ptr = sosimplefunc;
	printf("%p \n", ptr);

	return 0;
}