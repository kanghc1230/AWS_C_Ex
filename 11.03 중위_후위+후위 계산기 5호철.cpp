
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;	//������ū
static int icp[] = { 20 ,19 , 12 , 12 , 13 , 13 , 13 , 0 };	//���ؿ� ���Խ� �켱���� �񱳿�
static int isp[] = { 0 , 19 , 12 , 12 , 13 , 13 , 13 , 0 }; //���ؿ� ������ �켱���� �񱳿�
#define MAX 100
#define NUMBER '0'

char expr[MAX];	//�������Ĺ���

precedence stack[MAX];	//��ȯ����
int top = 0;			//stock������ ��ġ
void print_token(precedence);	//��ȯ�������
void add_token(int*, precedence );	//��ȯ�����߰�
precedence delete_token(int*);//��ȯ���û���

char expr2[MAX]; //��������
int expr2_num = 0;

double val[MAX];//��꽺��
int sp = 0;		//val������ ��ġ
void push(double);	//��꽺���߰�
double pop(void);	//��꽺�û���

void negative();	//���������Լ�

precedence get_token(char* symbol, int* n)	//����(symbol������, n��°���۵���)  precdence�� ã���ִ� �Լ�
{
	*symbol = expr[(*n)++];		// ���ڹ迭[n++]���� symbol�� �ְ�
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;

	default: return operand; //�⺻���� �ǿ�����(����)
	}
}

void print_token(precedence item) {	//����Լ� (�� �ٲﰪ����)
	switch (item) {
	case 2:
		expr2[expr2_num++] = '+'; expr2[expr2_num++] = ' '; break;
	case 3:
		expr2[expr2_num++] = '-'; expr2[expr2_num++] = ' '; break;
	case 4:
		expr2[expr2_num++] = '*'; expr2[expr2_num++] = ' '; break;
	case 5:
		expr2[expr2_num++] = '/'; expr2[expr2_num++] = ' '; break;
	case 6:
		expr2[expr2_num++] = '%'; expr2[expr2_num++] = ' '; break;
	}
}

void add_token(int* top, precedence item) {
	stack[++(*top)] = item;	//����++top�� �� �ֱ�
}
precedence delete_token(int* top) {
	return stack[(*top)--];
}
void push(double p)	//���ؿ� Ǫ��
{
	val[sp++] = p;
}
double pop(void) {
	return val[--sp];
}

void postfix(void)
{
	char symbol;
	precedence token;
	int n = 0;			//expt n��°

	stack[0] = eos;

	for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
	{	//�ʱⰪtoken = precedence;		token == eos;�鳡. token = precedence;�������

		if (token == operand) {	// operand�ǿ�����(����)�� ������ �ٷ����
			expr2[expr2_num++] = symbol;
			expr2[expr2_num++] = ' ';
		}
		else if (token == rparen)	//rparen )������ȣ��������
		{
			while (stack[top] != lparen)	// laparen'('�ް�ȣ�� ���ö�����
				print_token(delete_token(&top));
			delete_token(&top);
		}
		else	//�׿ܿ� �����ڰ� +-/*&\0�� ������, ���ؿ��ְ�, symbol isp�� token�� icp�� �� ���
		{
			while (isp[stack[top]] >= icp[token])
				print_token(delete_token(&top));
			add_token(&top, token);
		}
	}
	while ((token = delete_token(&top)) != eos) //token�� eos�����ö����� stack�� �ִ� ������ �� ���
		print_token(token);
	printf("\n");
}

//postfix�Լ� �ȿ��� expr�ȿ� ��� //�Ѵ��� token = get_token(*symbol,*n);

void read_line(char* input, int len) //���������Է��Լ�
{
	int i = 0;

	while (((input[i++] = getchar()) != '\n') && i < len);	//����ġ�ų� �ִ�100����
	input[--i] = '\0';

	if (i >= len) {											//���� 100�ʰ�
		printf("EEROR1 ������ �ʹ� ��ϴ�. MAX=100");
		exit(1);
	}
}
int main(void)
{
	int type;

	read_line(expr, MAX);	//���������Է��Լ�

	printf("expr : %s \n", expr);

	postfix();

	printf("expr2 : %s \n", expr2);

	return 0;
}