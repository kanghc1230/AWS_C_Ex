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

	//IF�� ù���� ����� ���� ���ϴ� üũ
	// 
	//����϶� �׳� �о�� If((num&1)==0)



	unsigned int check2 = 0x00000001;	//����Ʈ��ŧ �񱳰�  ///NUM�� (���)�⺻signed���⿡ ����Ʈ��ŧ�� ������ 1��������. (��)unsigned int num�̸� �⺻0������

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

	//�����ϋ�if((num&1) ==0)


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
