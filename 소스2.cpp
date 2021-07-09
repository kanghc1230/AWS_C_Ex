
#include<stdio.h>//03-02 실수의 문자열로 변환
#include<string.h>
#include<math.h>
void reverse(char s[])
{
	int c, x, z;
	for (x = 0, z = strlen(s) - 1; x < z; x++, z--) {
		c = s[x];
		s[x] = s[z];
		s[z] = c;
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
	//int counttemp = 0;
	//int countlen = 0; //소수부분길이
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
	printf("정수부분 %d \n", input2);	//123.00
	printf("소수부분 %f \n\n", input3); //0.456
	/*
	counttemp = input4;
	countlen = callcount(counttemp); //자리수세기
	input4 /= pow(10,6-countlen);	// 쓸모없는 0값빼기
	*/ 
	str[i++] = '.';
	//정수부분연산
	do {
		str[i++] = input2 % 10 + '0';	//정수의 10나머지연산 +'0'을 더해 문자화
	} while ((input2 /= 10) > 0);

	if (sign < 0)
		str[i++] = '-';

	str[i] = '\0'; //0자리

	reverse(str);//정수부분리버스

	input4 = 1; //실수부분은 그대로 str에 투입
	do {
		input3 *= 10;						//4.56
		input4 = input3;					//4 = 4.56
		str[i++] = input4 % 10 + '0';		//str[i++] = '4'
		input3 -= input4;					//4.56 - 4 
	} while (input4 > 0);	// input4 = input3 *10=0이 나오면 끝

	str[i++] = '\0'; //배열맨마지막에 \0

	printf("%s \n", str);
	return 0;
}