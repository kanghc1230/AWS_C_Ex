
#include<stdio.h>//03-02 �Ǽ��� ���ڿ��� ��ȯ
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
	//int countlen = 0; //�Ҽ��κб���
	char str[20];
	int i = 0;
	int j = 0;
	float sign = 0;

	scanf_s("%f", &input); //�Ǽ��ޱ�
	sign = input;

	if (sign < 0)
		input = -input;

	input2 = input; //�����κ� ����
	input3 = input - input2; //�Ҽ��κ�����
	printf("�����κ� %d \n", input2);	//123.00
	printf("�Ҽ��κ� %f \n\n", input3); //0.456
	/*
	counttemp = input4;
	countlen = callcount(counttemp); //�ڸ�������
	input4 /= pow(10,6-countlen);	// ������� 0������
	*/ 
	str[i++] = '.';
	//�����κп���
	do {
		str[i++] = input2 % 10 + '0';	//������ 10���������� +'0'�� ���� ����ȭ
	} while ((input2 /= 10) > 0);

	if (sign < 0)
		str[i++] = '-';

	str[i] = '\0'; //0�ڸ�

	reverse(str);//�����κи�����

	input4 = 1; //�Ǽ��κ��� �״�� str�� ����
	do {
		input3 *= 10;						//4.56
		input4 = input3;					//4 = 4.56
		str[i++] = input4 % 10 + '0';		//str[i++] = '4'
		input3 -= input4;					//4.56 - 4 
	} while (input4 > 0);	// input4 = input3 *10=0�� ������ ��

	str[i++] = '\0'; //�迭�Ǹ������� \0

	printf("%s \n", str);
	return 0;
}