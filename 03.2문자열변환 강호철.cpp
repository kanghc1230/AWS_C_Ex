/*
�߰���, �Ǽ��� �Է����� �޾Ƽ� ���ڿ��� ���� ��½��� �ִ� ���α׷��� ¥�ÿ�.
-	���� 40 page ���� �ϼ���
�Է��� scanf(��%f��, &num);
����� str�迭�� ���� �� ��, �������� �ݵ�� ��\0�� ���� ��
����� printf(��%s\n��, str);  // ��µ� ��, ������ ���� ���� ����.

//�Ҽ����̻�num1�� �Ҽ�������num2
*/
#include<stdio.h>//03-02 �Ǽ��� ���ڿ��� ��ȯ
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
	int countlen = 0; //�Ҽ��κб���
	char str[20];
	char str2[20];
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
	//0.456 ����
	input3 *= 10; //4.56
	input4 = input3;	//4 = 4.56
	do {
		str2[j++] = input4 % 10 + '0';		//str[i] = 4
		input3 -= input4;					//0.56 0xxx
		input3 *= 10;						//5.6
		input4 = input3;					//5 = 5.6
		//������ 10���������� +'0'�� ���� ����ȭ
	} while (input4 > 0);	// input4���� input3*10=0�� ������ ��

	//�Ҽ���
	str[i++] = '.';

	//�����κп���
	do {
		str[i++] = input2 % 10 + '0';	//������ 10���������� +'0'�� ���� ����ȭ
	} while ((input2 /= 10) > 0);

	if (sign < 0)
		str[i++] = '-';

	str2[j++] = '\0';
	str[i++] = '\0'; //�迭�Ǹ������� \0

	reverse(str);

	printf("%s%s \n", str, str2);
	return 0;
}



/*
#include<stdio.h>//03-02 �Ǽ��� ���ڿ��� ��ȯ
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
	int countlen = 0; //�Ҽ��κб���
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
	printf("�����κ� %d \n", input2);	//xx.00
	printf("�Ҽ��κ� %f \n\n", input3); //0.xxxx

	input3 = input3 * 1000000; //10^6���� �ڸ���ǥ��.  �Ǽ��� �����̳� *j������ �ȵǴ�������?
	input4 = input3;
	/*
	counttemp = input4;	
	countlen = callcount(counttemp); //�ڸ�������
	input4 /= pow(10,6-countlen);	// ������� 0������
	*/
	do {
		str[i++] = input4 % 10 + '0';	//������ 10���������� +'0'�� ���� ����ȭ
	} while ((input4 /= 10) > 0);

	//�Ҽ���
	str[i++] = '.';		

	//�����κп���
	do {
		str[i++] = input2 % 10 + '0';	//������ 10���������� +'0'�� ���� ����ȭ
	} while ((input2 /= 10) > 0);
	
	if (sign < 0)
		str[i++] = '-';

	str[i++] = '\0'; //�迭�Ǹ������� \0

	reverse(str);

	printf("%s \n", str);
	return 0;
}
*/