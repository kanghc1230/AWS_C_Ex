#include<stdio.h>
int main(void)
{
	int num = 0;	//�Է°�
	int i = 0;
	int n = 0;	//��
	unsigned int check = 0x80000000; //�񱳰�
	int buffer = 0;

	scanf_s("%d %d", &num, &n);

	for (i = 0; i < 32; i++)	 //����� ����¹�
	{
		if ((num & check) == 0) {
			printf("0");
			check = check >> 1;
		}
		else {
			printf("1");
			check = check >> 1;
		}
	}
	printf("\n");


	check = 0x80000000;

	for (i = 0; i < n; i++)		//����Ʈ ��ŧ���̼�
	{
		if ((num & check) == 0)
			num = num << 1;

		else {
			num = num << 1;
			num = num | 0x00000001;
		}
	}


	for (i = 0; i < 32; i++)	//����� ����¹�
	{
		if ((num & check) == 0) {
			printf("0");
		}
		else {
			printf("1");
		}
		check = check >> 1;
	}


	return 0;
}


