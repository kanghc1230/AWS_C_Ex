#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h> //strlen()������?

int main() //03�Ǽ���ȯ
{
	char str[20];
	int i,j = 0;
	int sign = 0;	//��ȣ
	float num1 = 0;
	float num2 = 0;
	float num1value = 0;
	float num2value = 0;
	float value = 0;	//���
	////////////////////////////

	scanf("%s", str);
	j = strlen(str);	//�ִ��������
	// str[j + 1] = '\0';	//�ܾ� ������0 scanf ���� �������� �׻� \0 �ڵ����� ä����

	if (str[0] == '-')		//ù �ڸ� sign��ȣ�Ǻ�
	{
		i = 1;
		sign = -1;
	}
	else {
		i = 0;
		sign = 1;
	}

	for (; str[i] != '.'; i++) 	// �տ��� �Ҽ���(��.��) ���� �� ����     i���� +1Ž������
	{
		num1 = str[i] - '0';		// num1�� str���ڷ� ��ȯ
		num1value = num1value * 10 + num1;	// �Ҽ��� �̻� ��� num1value������
	}
	for (; str[j - 1] != '.'; j--)	// ������ �Ҽ���(��.��) ���� �� ���� forŽ��   j-1���� -1Ž��
	{
		num2 = str[j - 1] - '0';	//num2�� str���ڷ� ��ȯ
		num2value = num2value / 10 + num2 / 10;	// �Ҽ��� ���� ���  num2value������
	}

	value = sign * (num1value + num2value); // ��� = ��ȣ*(xxx.xxx)

	printf("%f \n %f + %f ��ȣ:%d \n", value, num1value, num2value, sign);
	return 0;
}