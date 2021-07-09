#include<stdio.h>
void showalldata(const int* arr, int len)
{
	int i;
	for(i=0; i<len; i++)
		printf(" % d", arr[i]);
} //상수형태 arr배열받기


int main(void)	//포인터와 상수 문자열 포인터
{
	int num1 = 10; int num2 = 20; 
	int* ptr1 = &num1;
	int* ptr2 = &num2;
	*ptr1 += 10;
	*ptr2 -= 10;
	int arr[3][3] = { 1,2,3,4,5,6,7 };

	char str1[] = "We are the team";	//변수형태
	//char * str2 = "your team";	//상수형태 문자열 변경불가능 근데302p ERROR ????
	//char * str = "Hello, Pointer!";
	//char* strArr[3] = { "Simple", "String", "Array" }; Error 306p

	printf("%d %d \n", *ptr1, *ptr2);

	ptr1 = &num2;
	ptr2 = &num1;

	printf("%d %d \n" ,*ptr1, *ptr2);

	*ptr1 = 12;

	printf("%d %d \n", *ptr1, *ptr2);

	printf("%d", arr[1][2]);

	return 0;
}