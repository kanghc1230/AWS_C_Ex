#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void)
{
	unsigned int num = 0;	//입력값 unsigned로 변환
	int i = 0;
	int n = 0;	//수
	unsigned int check = 0x80000000; //비교값

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



	//대괄호IF문 첫글자 양수와 음수 비교하는 체크
	// 
	//양수일땐 그냥 밀어내기 If((num&1)==0)

	unsigned int check2 = 0x00000001;	//라이트서큘 비교값  /// (산수)기본signed num 1 (논리)unsigned num이면 0
	if (num >= 0) {
		for (i = 0; i < n; i++)		//라이트 서큘레이션
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
	//음수일땐
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

/*if((num&0x800000)==0)
		num=num<<1
  else
		2문장

*/


