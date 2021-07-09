#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;	//������ū
static int icp[] = { 20 ,19 , 12 , 12 , 13 , 13 , 13 , 0 };	//���ؿ� ���Խ� �켱���� �񱳿�
static int isp[] = { 0 , 19 , 12 , 12 , 13 , 13 , 13 , 0 }; //���ؿ� ������ �켱���� �񱳿�
#define MAX 100
#define NUMBER '0'

char expr[MAX];	//�������Ĺ���
precedence stack[MAX]; //���ñ���: enum precedence
int top = 0;		//expr��������ġ

char expr2[MAX]; //�������Ĺ���
int expr2_num = 0;

precedence get_token(char* symbol1, char* symbol2, char* symbol3, int* n)	//����(symbol������, n��°���۵���)  precdence�� ã���ִ� �Լ�
{
	char expr_buffer0 = -1;	//�������� �ʱⰪ-1
	char expr_buffer1;		//n������ġ '-'����,���� �Ǻ��� ����
	char expr_buffer2;		//n+1
	char expr_buffer3;		//n+2

	if (*n > 0)
		expr_buffer0 = expr[(*n) - 1]; //�� ���ں�ȣȮ��
	expr_buffer1 = expr[*n];		//ù��°char���� -
	expr_buffer2 = expr[(*n) + 1];	//�ι�°char���� 1
	expr_buffer3 = expr[(*n) + 2];	//����°char���� 0

	*symbol1 = expr[(*n)++];	//ù�ܾ� �ɺ�1
	*symbol2 = 0;	//�⺻0 �ɺ�2
	*symbol3 = 0;	//�⺻0 �ɺ�3

	//-�� ���ö�
	if (expr_buffer1 == '-' )
	{
		if (isdigit(expr_buffer0) || expr_buffer0 == ')') { // ������'-'
			return minus;
		}
		else {						// ��ȣ'-'+ �ڸ���
			if (isdigit(expr_buffer2)) {	//ù°�ڸ��� ���ڶ��
				if (isdigit(expr_buffer3)) {	//��°�ڸ��� ���ڶ��
					*symbol2 = expr[(*n)++];
					*symbol3 = expr[(*n)++];
					return operand;
				}
				else {						//��°�ڸ��� ���ڰ��ƴϸ�
					*symbol2 = expr[(*n)++];
					return operand;
				}
			}
		}
	}

	//���ڸ��� ����϶�
	if (isdigit(expr_buffer1) && expr_buffer1 !='-') {	//ù��°���� ���ڰ� '-'���ƴϸ�
		if (isdigit(expr_buffer2)){	//��°�ڸ����� ������ 
			*symbol2 = expr[(*n)++];	//��°�ڸ����� ����
			return operand;
		}
	}

	switch (*symbol1) {
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

void print_token(precedence item) {	//pop�� ��� (�ٲﰪ���ް� delete������)
	expr2[expr2_num++] = ' ';
	switch (item) {
	case 2:
		printf("+"); expr2[expr2_num++] = '+'; break;
	case 3:
		printf("-"); expr2[expr2_num++] = '-'; break;
	case 4:
		printf("*"); expr2[expr2_num++] = '*'; break;
	case 5:
		printf("/"); expr2[expr2_num++] = '/'; break;
	case 6:
		printf("%"); expr2[expr2_num++] = '%'; break;
	}
	expr2[expr2_num++] = ' ';
}
void add_token(int* top, precedence item) {
	if (*top >= MAX - 1) {				//���ÿ��� top�� �ִ�ġ��
		printf("EEROR2 ������ �� á���ϴ�. ��� �߰��� �Ұ����մϴ�");
		exit(2);
	}
	stack[++(*top)] = item;	//����++top�� �� �ֱ�
}

precedence delete_token(int* top) {
	if (*top == -1)
		printf("������ ������ϴ�");
	return stack[(*top)--];
}

void postfix(void)
{
	char symbol;	//ù�ڸ��� ���� ����
	char symbol2;	//���ڸ��� ���� ����
	char symbol3;	//ù�ڸ��� -��� ���ڸ����� ���� ����
	precedence token;
	int n = 0;			//expt n��°

	stack[0] = eos;

	for (token = get_token(&symbol, &symbol2, &symbol3, &n); token != eos; token = get_token(&symbol, &symbol2, &symbol3, &n))
	{	//�ʱⰪtoken = precedence;		token == eos;�鳡. token = precedence;�������

		if (token == operand) {	// operand�ǿ�����(����)�� ������ �ٷ����
			printf("%c", symbol);

			expr2[expr2_num++] = symbol;
			if (symbol2 != 0) {
				expr2[expr2_num++] = symbol2;
				printf("%c", symbol2);
			}
			if (symbol3 != 0) {
				expr2[expr2_num++] = symbol3;
				printf("%c", symbol3);
			}
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
