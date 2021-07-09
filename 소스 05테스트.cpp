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

	//IF문 첫글자 양수와 음수 비교하는 체크
	// 
	//양수일땐 그냥 밀어내기 If((num&1)==0)



	unsigned int check2 = 0x00000001;	//라이트서큘 비교값  ///NUM가 (산수)기본signed였기에 라이트서큘시 왼쪽이 1로차더라. (논리)unsigned int num이면 기본0으로참

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

	//음수일떈if((num&1) ==0)


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
