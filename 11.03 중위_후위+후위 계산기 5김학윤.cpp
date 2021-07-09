#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // isdigit()

#define MAX 100
#define NUMBER '0'

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };

char expr[MAX]; // �Է¹޴� ����
char postfix_expr[MAX]; // ���� ����� ����

precedence stack[MAX]; // ������ �ӽ� ����
double val[MAX]; // ���갪 ����ִ� ����



int top; // ������ �ӽ� ������ ����Ű�� �ε���
int index; // ���갪 ����ִ� ������ ����Ű�� �ε��� 

void postfix(void); // ���� �����ڷ� �ٲ��ִ� �Լ�
precedence get_token(char*, int*); // char���� precedence���� �ٲ��ִ� �Լ�
char put_token(precedence); // precedence�� char������ �ٲ��ִ� �Լ�
void add(precedence); // ������ �ӽ� ������ �߰��ϴ� �Լ�
precedence adelete(); // ������ �ӽ� ������ �����ϴ� �Լ�
void push(double); // ���� ���� ����� �����͸� �ִ� �Լ�
double pop(void); // ���� ���� ����� �����͸� ������ �Լ�
int get_op(char[], int*); // ���� �����ڸ� �����ϴ� �Լ�

void calculator(); // ���� ����� ����� �ϴ� �Լ�

void test_negative(); // negative �����Լ�

int main()
{
	/*���� �Է� �κ�*/
	scanf("%s", expr);

	test_negative();

	printf("%s\n", expr);

	postfix();

	printf("%s\n", postfix_expr);
	calculator();

	return 0;
}

void test_negative()
{
	int i = 0;
	while (expr[i] != '\0')
	{
		if (expr[i] == '-')
		{
			if (!isdigit(expr[i - 1]) && expr[i - 1] != ')') // ���� ���� ���ڰ��ƴϰų� �����ʰ�ȣ�� �ƴҰ�츸 �װ�Ƽ�� �ν�
				expr[i] = 'n';
		}
		i++;
	}
}


void calculator()	//���
{
	int i = 0;
	int type;
	char number[MAX];
	double op2;


	while (postfix_expr[i] != '\0')
	{
		type = get_op(number, &i);

		switch (type)
		{
		case NUMBER:
			push(atof(number));
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
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			push((int)pop() % (int)op2);
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", number);
			break;
		}
	}

	printf("�����: %f\n", pop());

}

int get_op(char number[], int* i)
{
	int n, c;
	int negative_count = 0;

	//printf("postfix_expr[%d]: %c\n", *i, postfix_expr[*i]);


	while (postfix_expr[*i] == ' ' || postfix_expr[*i] == '\t') 
		(*i)++; // ���� ����

	while (postfix_expr[*i] == 'n')
	{
		negative_count++;
		(*i)++;
	}

	number[0] = '\0';
	if (!isdigit(postfix_expr[*i]) && postfix_expr[*i]) 
		return postfix_expr[(*i)++]; // ���� ���

	n = 0;
	if (negative_count % 2 != 0)	
	{
		number[n++] = '-';
	}

	while (isdigit(postfix_expr[*i]) || postfix_expr[*i] == '.')
		number[n++] = postfix_expr[(*i)++];

	number[n] = '\0';

	printf("number: %s\n", number);

	return NUMBER;
}


void postfix()
{
	int i = 0;
	int is_negative = 0;
	int is_operand = 0;
	char symbol;
	precedence token;
	int n = 0;

	stack[top++] = eos;

	for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
	{
		if (token != operand && token != lparen)
			postfix_expr[i++] = ' '; // ���ڸ� ���� ������ ���� ���� �߰� 

		/* ���ǰ� ó�� �κ� ����*/

		if (expr[n] == 'n')
		{
			if (expr[n + 1] == '(')
			{
				is_negative = 1;
				n++;
			}

		}
		if (expr[n + 1] == '(')
			is_negative = 0;

		if (token == rparen)
			is_negative = 0;

		if (token != operand)
			is_operand = 1;
		/* ���� �� ó�� �κ� ��*/



		if (token == operand)
		{
			if (is_negative && is_operand)
			{
				postfix_expr[i++] = 'n';

				is_operand = 0;
			}

			postfix_expr[i++] = symbol;
		}

		else if (token == rparen) {
			/* ���� ��ȣ�� ���� ������ ��ū���� �����ؼ� ��½�Ŵ */
			while (stack[top - 1] != lparen)
				postfix_expr[i++] = put_token(adelete());
			adelete();
		}
		else {
			/* symbol�� isp�� token�� icp ���� ũ�ų� ������ symbol�� �����ϰ� ��½�Ŵ */
			while (isp[stack[top]] >= icp[token])
				postfix_expr[i++] = put_token(adelete());

			add(token);
		}
	}

	while ((token = adelete()) != eos)
		postfix_expr[i++] = put_token(token);

	postfix_expr[i++] = '\0';

}

/////////////////////////////////////////////////////////////////////////////////////


precedence get_token(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

char put_token(precedence token)
{
	switch (token)
	{
	case plus: return '+';
	case minus: return '-';
	case divide:return '/';
	case times: return '*';
	case mod: return '%';
	case eos: '\0';
	}
}


void add(precedence token)
{
	stack[top++] = token;
}

precedence adelete()
{
	return stack[--top];
}

void push(double d)
{
	val[index++] = d;
}

double pop(void)
{
	return val[--index];
}







