//�ǽ�) 
//1. �־��� ���ڿ����� �� �ٸ� �־��� ���ڸ� �����ϰ� ������ �Ŀ�, 
//2. ����ȭ ��Ų ���ڿ��� ����� �ִ� �Լ� revsqueeze(s, c) �� ����ÿ�.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *resqueeze(char*, char*);
int main()
{
	char s[20];	//�־��� ���ڿ� ����s
	int i = 0;	//�ӽú���
	char c;		//������ ���ڿ� ����c
	char* result;	//resqueeze �����(�ּ�)�� ���� result������

	while ((s[i++] = getchar()) != '\n') //�־��� ���ڿ��ޱ�
		;	//true
	s[i--] = '\0';

	c = getchar();	//������ ���ڿ��ޱ�

	result = resqueeze(s, &c);		//s�� c �ּҷ� ���� 
	
	printf("%s", result);	//result�� �Լ������ �ּҰ��޾Ƽ� ���

	return 0;
}

char* resqueeze(char* ps, char* pc)	//�����ͷι���
{
	int i = 0;
	int j = 0;
	int len = strlen(ps);

	ps = ps + len - 1; // ps�� �ּҰ��� +����, ��-1ĭ. �ּ�ps������ s���ڿ��� ���� �ּҸ� ����Ŵ.
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	char *temp = (char*)malloc(len + 1);	//������temp��, len+1ũ�⸸ŭ �����ϰ� �޸��ּ� ����Ŵ.
							  //���� ���⿡ len�̾ƴ϶� strlen(ps)�� ��������� �ٷ����� ps��ġ�� �ٲ� len=1�̉����ž�.
							  //������߳��͵� malloc���� �Ѿ�� ���ԷµǸ� ������ ���߿� ����������־� 
	for (i = 1; i<len; i++)
	{
		ps--;
		if (*(ps) == *pc)			//ps-i�� ����Ű�°� ���� == pc ����Ű�°� ���� ������ �ѱ��
			;
		else{
			*(temp + j) = *(ps);
			j++;
		}
	}
	*(temp + j) = '\0';		//temp�����Ͱ� ����Ű�� malloc������ len-1��ġ��, �� = null
	
	return temp;	//return char* resqueeze 
}