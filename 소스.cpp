#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void)
{
	unsigned int num = 0;	//�Է°� unsigned�� ��ȯ
	int i = 0;
	int n = 0;	//��
	unsigned int check = 0x80000000; //�񱳰�

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



	//���ȣIF�� ù���� ����� ���� ���ϴ� üũ
	// 
	//����϶� �׳� �о�� If((num&1)==0)

	unsigned int check2 = 0x00000001;	//����Ʈ��ŧ �񱳰�  /// (���)�⺻signed num 1 (��)unsigned num�̸� 0
	if (num >= 0) {
		for (i = 0; i < n; i++)		//����Ʈ ��ŧ���̼�
		{
			if ((num & check2) == 0) {
				num = num >> 1;
			}

			else {
				num = num >> 1;
				num = num | 0x80000000;
			}
		}
	}
	//�����϶�
	else {
		for (i = 0; i < n; i++)
		{
			if ((num & check2) == 0) {
				num = num >> 1;
				num = num | 0x80000000;
			}
			else {
				num = num >> 1;
			}
		}

	}



	check = 0x80000000;
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

/*if((num&0x800000)==0)
		num=num<<1
  else
		2����

*/


