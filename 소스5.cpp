#include<stdio.h>
void showalldata(const int* arr, int len)
{
	int i;
	for(i=0; i<len; i++)
		printf(" % d", arr[i]);
} //������� arr�迭�ޱ�


int main(void)	//�����Ϳ� ��� ���ڿ� ������
{
	int num1 = 10; int num2 = 20; 
	int* ptr1 = &num1;
	int* ptr2 = &num2;
	*ptr1 += 10;
	*ptr2 -= 10;
	int arr[3][3] = { 1,2,3,4,5,6,7 };

	char str1[] = "We are the team";	//��������
	//char * str2 = "your team";	//������� ���ڿ� ����Ұ��� �ٵ�302p ERROR ????
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