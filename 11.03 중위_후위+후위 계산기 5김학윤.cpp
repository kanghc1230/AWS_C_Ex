#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // isdigit()

#define MAX 100
#define NUMBER '0'

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };

char expr[MAX]; // 입력받는 수식
char postfix_expr[MAX]; // 후위 연산된 수식

precedence stack[MAX]; // 연산자 임시 스택
double val[MAX]; // 연산값 집어넣는 스택



int top; // 연산자 임시 스택을 가르키는 인덱스
int index; // 연산값 집어넣는 스택을 가르키는 인덱스 

void postfix(void); // 후위 연산자로 바꿔주는 함수
precedence get_token(char*, int*); // char형을 precedence으로 바꿔주는 함수
char put_token(precedence); // precedence를 char형으로 바꿔주는 함수
void add(precedence); // 연산자 임시 스택을 추가하는 함수
precedence adelete(); // 연산자 임시 스택을 삭제하는 함수
void push(double); // 후위 연산 결과에 데이터를 넣는 함수
double pop(void); // 후위 연산 결과의 데이터를 꺼내는 함수
int get_op(char[], int*); // 숫자 연산자를 구분하는 함수

void calculator(); // 후위 연산식 계산을 하는 함수

void test_negative(); // negative 변경함수

int main()
{
	/*수식 입력 부분*/
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
			if (!isdigit(expr[i - 1]) && expr[i - 1] != ')') // 앞의 값이 숫자가아니거나 오른쪽괄호가 아닐경우만 네거티브 인식
				expr[i] = 'n';
		}
		i++;
	}
}


void calculator()	//계산
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

	printf("결과값: %f\n", pop());

}

int get_op(char number[], int* i)
{
	int n, c;
	int negative_count = 0;

	//printf("postfix_expr[%d]: %c\n", *i, postfix_expr[*i]);


	while (postfix_expr[*i] == ' ' || postfix_expr[*i] == '\t') 
		(*i)++; // 공백 제거

	while (postfix_expr[*i] == 'n')
	{
		negative_count++;
		(*i)++;
	}

	number[0] = '\0';
	if (!isdigit(postfix_expr[*i]) && postfix_expr[*i]) 
		return postfix_expr[(*i)++]; // 문자 출력

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
			postfix_expr[i++] = ' '; // 두자리 수를 나누기 위한 공백 추가 

		/* 음의값 처리 부분 시작*/

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
		/* 음의 값 처리 부분 끝*/



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
			/* 왼쪽 괄호가 나올 떄까지 토큰들을 제거해서 출력시킴 */
			while (stack[top - 1] != lparen)
				postfix_expr[i++] = put_token(adelete());
			adelete();
		}
		else {
			/* symbol의 isp가 token의 icp 보다 크거나 같으면 symbol을 제거하고 출력시킴 */
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







