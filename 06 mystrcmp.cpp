#include<stdio.h>
#include<string.h>
//������ ���� �������� 

int mystrcmp(char[], char[]);				//���ڿ� 2�� ���Լ� �迭2�� ���ڷι޾ƿ�������
											//���� �̸��� �Ʒ����� �����Ҷ���
int main(void) 
{
	char s[20];		//ù��° ���� ���ڿ�
	char t[20];		//�ι�° ���� ���ڿ�
	int i = 0;		//�ӽú���i
	int j = 0;		//�ӽú���j
	int value = 0;	//�������¿뺯��

	while ((s[i] = getchar()) != '\n')		//s[i]�� ���ʴ�� getchar(), \n����ĥ������
		i++;
	s[i] = '\0';	//\n��� ��\0�ֱ�		
	//������ while ((s[i++] = getchar()) != '\n');������ �ٳ����� i�� �ڵ������� ++�Ǳ⿡ s[--i] = \0;��
											
	while ((t[j] = getchar()) != '\n')	
		j++;
	t[j] = '\0';

	value = mystrcmp(s, t);		// mystrcmp == s>t�� 1, t<s�� -1, t=0�̸� 0�� �����ϴ� �Լ�
								// ���� s, t �ּҰ� ����. ���� �迭�̴ϱ� �� s,t
	printf("%d", value);

	return 0;
}

int mystrcmp(char ps[], char pt[])	//�迭�� �̷��� �� ps[]�� ���� 
{
	int a = strlen(ps);	
	int b = strlen(pt);
	int len;

	if (a >= b)		//���̰� ������ len
		len = a;	
	else
		len = b;

	//	for (int i = 0; pt[i] != '\0' || ps[i] != '\0' ; i++)�� ���̺� ���ʿ�x. �����ڼ��� != || |
	for (int i = 0; i < len; i++)	//���̱�ͱ��� ��
	{
		if (ps[i] > pt[i])		//ps[i]�� ũ�� 1����
			return 1;
		else if (ps[i] < pt[i])	//pt[i]�� ũ�� -1����
			return -1;
		else					//ps,pt[i]�� ������ ��true �ٽ� for������
			;
	}
	return 0;	//�Ѵٰ����� 0����
}
