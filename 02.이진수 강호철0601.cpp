#include<stdio.h>
int main(void)
{
	int num=0;
	unsigned int check = 0x80000000;			//unsigned int check �߿��� �׽�Ʈ
	
	scanf_s("%d", &num);		//scanf("%d", &num);

	for (int i = 0; i < 32; i++)
	{
		//for������ i%4==0���� 4ĭ����' '�ֱ�

		if((num&check)==0){
			printf("0");
			check = check >> 1;
			}
		else {
			printf("1");
			check = check >> 1;
		}

		//���� �ߺ��Ǵ� check���� ������ ���������� check = check >> 1;
	}

	// printf("\n"); �ʱ�ȭ�� �Ϲ�����

	return 0;
}


