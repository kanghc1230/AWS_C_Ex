#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) //05����Ʈ��Ŭ���ñ�
{
	int num = 0;	//�Է°� unsigned�� ��ȯ
	int i = 0;
	int n = 0;	//��
	unsigned int check = 0x80000000; //�񱳰�
	unsigned int check2 = 0x7fffffff;
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
	check2 = 0x7fffffff;
	//t1. ���ȣIF�� ù���� ����� ���� ���ϴ� üũ
	// 
	//t2. ����϶� �׳� �о��
	
	for (i = 0; i < n; i++)  //if���ȿ� for���̾ȿ������� �� n����ŭ �۵��ؾ��ϴµ� �Ʒ� ������꿡 ������ ������ ó������
	{
		if(num >= 0) {  //����Ʈ ��ŧ���̼�	 ����϶����� 

				if ((num & 1) == 0) {
					num = num >> 1;
				}
				else {
					num = num >> 1;		
					num = num | check;	// 0�ڸ� 1��ä���ߵǼ� 0x80000000 1000 0000~�� or����
				}
		}
		//t3. �����϶� �ݴ�üũ�� ����
		else {
				if ((num & 1) == 0) {
					num = num >> 1;
					num = num & check2;	// num & 0x7fffffff 0111 1111~�� &���� // (check-1)�� ����ȯ�濡���� �ȵɼ������� ��������...
				}
				else {
					num = num >> 1;
				}
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

/*if((num&0x800000)==0)
		num=num<<1
  else
		2����

*/


