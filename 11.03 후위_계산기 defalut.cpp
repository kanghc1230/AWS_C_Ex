#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 100
#define NUMBER '0'
char expr[MAX];
char expr2[MAX];
int expr2_num = 0;

int getop(char[]);
void push(double);
double pop(void);

int sp = 0;
double val[MAX];
/////////////////////////////////
int main(void) {
	int type;
	double op2;
	char s[MAX];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error 0�� �����������ϴ�.");
			break;
		case '\n':
			printf("\t%.8g \n", pop());
			break;
		default:
			printf("error �˼����� ��ɾ�");
			break;
		}
	}
	return 0;
}

void push(double f)
{
	if (sp < MAX)
		val[sp++] = f;
	else
		printf("error ������ ������ �����������ϴ�.");
}

double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error3 ������ ������ϴ�");
		return 0.0;
	}
}
//����ǥ���� �޴� �Լ�. ���Ĺ޾Ƽ� ����ϱ��� �����ϴ� gettop
int getop(char s[]) {
	//��������expr�� ���ο��� �����ڱ� getchar()�ϰ� s[i] = '\0'�־ char���常���;
	//getop�Լ� ��������,��������,����, '.'���� 
	//�ִ���ڼ������� ����ó��
	int i=0, c;
	char minus_buffer;

	while ((s[0] = c = getchar()) == ' ' || c == '\t');	//�����̰ų� \t�� ' ''\0'��������
	s[1] = '\0';
	
	if (!isdigit(c) && c != '.' && c !='-')	//���ڰ� �ƴϰų� '.'�̾ƴϸ�. + - / %�̸�
		return c;

	if (c == '-') {						//c�� -��
		minus_buffer = getchar();		//�������˻� 
		if (isdigit(minus_buffer)) {	// '-','����'�� ���� ��ӹ���
			s[++i] = minus_buffer;
			while (isdigit(s[++i] = c = getchar())); //\0�ް� ���� NUMBER�ΰ�
		}
		else {							// '-',' '�� ��ȣ�� ����c
			s[1] = '\0';
			return c;
		}
	}

	if (isdigit(c)) //���ڸ�
		while (isdigit(s[++i] = c = getchar()))
			;
	if (c == '.')	//'.;�̸�
		while (isdigit(s[++i] = c = getchar()))
			;
	s[i] = '\0';

	return NUMBER;
}
