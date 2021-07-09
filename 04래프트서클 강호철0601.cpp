#include<stdio.h>
int main(void)
{
	int num = 0;	//입력값
	int i = 0;
	int n = 0;	//수
	unsigned int check = 0x80000000; //비교값
	int buffer = 0;

	scanf_s("%d %d", &num, &n);

	for (i = 0; i < 32; i++)	 //결과값 비교출력문
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

	for (i = 0; i < n; i++)		//래프트 서큘레이션
	{
		if ((num & check) == 0)
			num = num << 1;

		else {
			num = num << 1;
			num = num | 0x00000001;
		}
	}


	for (i = 0; i < 32; i++)	//결과값 비교출력문
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


