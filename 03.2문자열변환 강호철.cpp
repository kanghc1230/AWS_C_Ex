/*
추가로, 실수를 입력으로 받아서 문자열로 만들어서 출력시켜 주는 프로그램을 짜시오.
-	교재 40 page 참조 하세요
입력은 scanf(“%f”, &num);
결과를 str배열에 저장 할 때, 마지막에 반드시 ‘\0’ 넣을 것
출력은 printf(“%s\n”, str);  // 출력될 때, 오차가 나올 수도 있음.

//소수점이상num1과 소수점이하num2
*/
#include<stdio.h>//03-02 실수의 문자열로 변환
#include<string.h>
#include<math.h>
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
/*
int callcount(int digit)
{
	count = 0;
	while ((digit % 10) != 0)
	{
		digit = digit / 10;
		++count;
	}
	return count;
}
*/
int main(void)
{
	float input = 0;
	int input2 = 0;
	float input3 = 0;
	int input4 = 0;
	int counttemp = 0;
	int countlen = 0; //소수부분길이
	char str[20];
	char str2[20];
	int i = 0;
	int j = 0;
	float sign = 0;

	scanf_s("%f", &input); //실수받기
	sign = input;

	if (sign < 0)
		input = -input;

	input2 = input; //정수부분 추출
	input3 = input - input2; //소수부분추출
	printf("정수부분 %d \n", input2);	//123.00
	printf("소수부분 %f \n\n", input3); //0.456
	/*
	counttemp = input4;
	countlen = callcount(counttemp); //자리수세기
	input4 /= pow(10,6-countlen);	// 쓸모없는 0값빼기
	*/
	//0.456 투입
	input3 *= 10; //4.56
	input4 = input3;	//4 = 4.56
	do {
		str2[j++] = input4 % 10 + '0';		//str[i] = 4
		input3 -= input4;					//0.56 0xxx
		input3 *= 10;						//5.6
		input4 = input3;					//5 = 5.6
		//정수의 10나머지연산 +'0'을 더해 문자화
	} while (input4 > 0);	// input4에들어갈 input3*10=0이 나오면 끝

	//소수점
	str[i++] = '.';

	//정수부분연산
	do {
		str[i++] = input2 % 10 + '0';	//정수의 10나머지연산 +'0'을 더해 문자화
	} while ((input2 /= 10) > 0);

	if (sign < 0)
		str[i++] = '-';

	str2[j++] = '\0';
	str[i++] = '\0'; //배열맨마지막에 \0

	reverse(str);

	printf("%s%s \n", str, str2);
	return 0;
}



/*
#include<stdio.h>//03-02 실수의 문자열로 변환
#include<string.h>
#include<math.h>
void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
/*
int callcount(int digit)
{
	count = 0;
	while ((digit % 10) != 0)
	{
		digit = digit / 10;
		++count;
	}
	return count;
}
*/
int main(void)
{
	float input = 0;
	int input2 = 0;
	float input3 = 0;
	int input4 = 0;
	int counttemp = 0;
	int countlen = 0; //소수부분길이
	char str[20];
	int i = 0;
	int j = 0;
	float sign = 0;
	
	scanf_s("%f", &input); //실수받기
	sign = input;

	if (sign < 0)
		input = -input;

	input2 = input; //정수부분 추출
	input3 = input - input2; //소수부분추출
	printf("정수부분 %d \n", input2);	//xx.00
	printf("소수부분 %f \n\n", input3); //0.xxxx

	input3 = input3 * 1000000; //10^6까지 자리수표현.  실수는 제곱이나 *j연산이 안되는이유는?
	input4 = input3;
	/*
	counttemp = input4;	
	countlen = callcount(counttemp); //자리수세기
	input4 /= pow(10,6-countlen);	// 쓸모없는 0값빼기
	*/
	do {
		str[i++] = input4 % 10 + '0';	//정수의 10나머지연산 +'0'을 더해 문자화
	} while ((input4 /= 10) > 0);

	//소수점
	str[i++] = '.';		

	//정수부분연산
	do {
		str[i++] = input2 % 10 + '0';	//정수의 10나머지연산 +'0'을 더해 문자화
	} while ((input2 /= 10) > 0);
	
	if (sign < 0)
		str[i++] = '-';

	str[i++] = '\0'; //배열맨마지막에 \0

	reverse(str);

	printf("%s \n", str);
	return 0;
}
*/