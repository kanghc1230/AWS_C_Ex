#include <stdio.h>
//394p �Լ� �����Ϳ� const

void simpleadder(int n1, int n2)
{
	printf("%d + %d = %d \n", n1, n2, n1 + n2);
}

void showstring(char* str)
{
	printf("%s \n", str);
}

int main(void)
{
	const char* str = "function pointer";	//c++������ const char* str = "function pointer"; ��� c������ char *str ="���ڿ�";�ص��ߵ�.
	
	int num1 = 10 , num2 = 20;

	void (*fptr1)(int, int) = simpleadder;	//�Լ� ������ ������ = �Լ���;
	void (*fptr2)(char *) = showstring;		//char * ?

	//�Լ� ������ ������ ���� �븮ȣ��

	fptr1(num1, num2);
	fptr2(str);			//���� ���������� cpp���� �ȵ� const �Լ��� ȣ��Ұ�? ����c�κ���õ�


	return 0;
}