//���ڿ� 2���޾ƿͼ� fcmp�� �з��ϰ� �����Լ� �����Ϳ��� �Լ�numcmp strcmp��. �񱳰����

#include<stdio.h>
#include<ctype.h>
#include<string.h>//strcmp
#include<stdlib.h> //atof
//strcmp ���ں��Լ� a>b 1 a<b -1 ������0
int numcmp(const char*, const char*); //���ں��Լ� a>b 1 a<b -1 ������0 
void fcmp(int (**p)(const char*, const char*), char* ps, char* pt);	//���ڼ��� �Ǵ��� �����Լ�,�����Լ�����
int main(void)
{
	char s[80];
	char t[80]; //��2��
	int (*ptr)(const char*, const char*);	//ptr�� ������for�Լ�

	scanf("%s %s", s, t);

	fcmp(&ptr, s, t); // ���ڼ��ڱ��� �Լ�fcmp(�Լ�������,�迭,�迭) �� //*ptr�� **p�� numcmpȤ�� strcmp�� ����

	printf("%d \n", ptr(s, t));		//ptr�� ������Լ� ��(s,t) ����Ʈ.
									//numcmp Ȥ�� strcmp
	return 0;
}

void fcmp(int (**p)(const char*, const char*), char* ps, char* pt)	//������ptr�� ���������ͷ�, s, t
{
	//psȮ��
	if (*ps == '-')	//-����
		ps++;
	while (*ps != '\0')
	{						//sdigit((*ps)-'0') isdigit�� ĳ���͸� �־����.���ڿ�!�� ���ڸ� true 1
		if (isdigit(*ps))	//*ps�� ���ڸ�
			ps++;			//�ּ� ps+1
		else if(*ps == '.') //*ps�� '.'�̸�
			ps++;
		else				//ps�� ���ڸ�
		{
			*p = strcmp;	//����������p�� ���ں��Լ� ����
			return;			//�Լ��� (����!) c���������� Ư���� void��� returnġ�� ���������ִ�.
		}
	}
	//ptȮ��
	if(*pt =='-')//-����
		pt++;
	while (*pt != '\0') 
	{
		if (isdigit(*pt))	//*ps�� ���ڸ�
			pt++;
		else if (*pt == '.')//*ps�� '.'�̸�
			pt++;
		else				//ps�� ���ڸ�
		{
			*p = strcmp;	//����������p�� ���ں��Լ� ����
			return;			//�Լ���
		}	
	}
	*p = numcmp;	//���ڿ��̾���.����������p�� ���ں��Լ� ����
}

int numcmp(const char* ps, const char* pt)	//num���Լ�
{
	float a, b;

	a = atof(ps);	//���� a,b�Ѵ� �Ǽ��ιٲٱ�
	b = atof(pt);	

	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}