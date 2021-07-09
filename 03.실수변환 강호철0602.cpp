#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h> //strlen()쓰려고?

int main() //03실수변환
{
	char str[20];
	int i,j = 0;
	int sign = 0;	//부호
	float num1 = 0;
	float num2 = 0;
	float num1value = 0;
	float num2value = 0;
	float value = 0;	//결과
	////////////////////////////

	scanf("%s", str);
	j = strlen(str);	//최대길이저장
	// str[j + 1] = '\0';	//단어 마지막0 scanf 사용시 마지막에 항상 \0 자동으로 채워짐

	if (str[0] == '-')		//첫 자리 sign부호판별
	{
		i = 1;
		sign = -1;
	}
	else {
		i = 0;
		sign = 1;
	}

	for (; str[i] != '.'; i++) 	// 앞에서 소수점(‘.’) 나올 때 까지     i부터 +1탐색까지
	{
		num1 = str[i] - '0';		// num1로 str숫자로 변환
		num1value = num1value * 10 + num1;	// 소수점 이상 결과 num1value에저장
	}
	for (; str[j - 1] != '.'; j--)	// 끝에서 소수점(‘.’) 나올 때 까지 for탐색   j-1부터 -1탐색
	{
		num2 = str[j - 1] - '0';	//num2로 str숫자로 변환
		num2value = num2value / 10 + num2 / 10;	// 소수점 이하 결과  num2value에저장
	}

	value = sign * (num1value + num2value); // 결과 = 부호*(xxx.xxx)

	printf("%f \n %f + %f 부호:%d \n", value, num1value, num2value, sign);
	return 0;
}