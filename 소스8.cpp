#include<stdio.h>
//void ������ (�ٱ��ϰ��� �Լ� �ּҰ� ��)
//�ٵ� ����,����=20�Ұ� �����Ϳ���++�Ұ� 
//���� �ּҰ����� �ǹ̸��ΰ� ���������� ���߿� �����Ҷ�, �����޸��Ҵ���

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