#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) //05라이트서클뭐시기
{
	int num = 0;	//입력값 unsigned로 변환
	int i = 0;
	int n = 0;	//수
	unsigned int check = 0x80000000; //비교값
	unsigned int check2 = 0x7fffffff;
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
	check2 = 0x7fffffff;
	//t1. 대괄호IF문 첫글자 양수와 음수 비교하는 체크
	// 
	//t2. 양수일땐 그냥 밀어내기
	
	for (i = 0; i < n; i++)  //if문안에 for문이안에있으면 총 n번만큼 작동해야하는데 아래 양수연산에 묶여서 음수를 처리못함
	{
		if(num >= 0) {  //라이트 서큘레이션	 양수일때연산 

				if ((num & 1) == 0) {
					num = num >> 1;
				}
				else {
					num = num >> 1;		
					num = num | check;	// 0자리 1로채워야되서 0x80000000 1000 0000~과 or연산
				}
		}
		//t3. 음수일땐 반대체크와 연산
		else {
				if ((num & 1) == 0) {
					num = num >> 1;
					num = num & check2;	// num & 0x7fffffff 0111 1111~과 &연산 // (check-1)은 지원환경에따라 안될수도있음 하지마라...
				}
				else {
					num = num >> 1;
				}
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

/*if((num&0x800000)==0)
		num=num<<1
  else
		2문장

*/


