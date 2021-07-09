#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;	//연산토큰
static int icp[] = { 20 ,19 , 12 , 12 , 13 , 13 , 13 , 0 };	//스텍에 진입시 우선순위 비교용
static int isp[] = { 0 , 19 , 12 , 12 , 13 , 13 , 13 , 0 }; //스텍에 있을때 우선순위 비교용
#define MAX 100
#define NUMBER '0'

char expr[MAX];	//중위수식받음
precedence stack[MAX]; //스택구조: enum precedence
int top = 0;		//expr스텍의위치

char expr2[MAX]; //후위수식받음
int expr2_num = 0;

precedence get_token(char* symbol1, char* symbol2, char* symbol3, int* n)	//인자(symbol포인터, n번째값작동중)  precdence를 찾아주는 함수
{
	char expr_buffer0 = -1;	//전값버퍼 초기값-1
	char expr_buffer1;		//n현재위치 '-'음수,수식 판별용 버퍼
	char expr_buffer2;		//n+1
	char expr_buffer3;		//n+2

	if (*n > 0)
		expr_buffer0 = expr[(*n) - 1]; //전 숫자부호확인
	expr_buffer1 = expr[*n];		//첫번째char버퍼 -
	expr_buffer2 = expr[(*n) + 1];	//두번째char버퍼 1
	expr_buffer3 = expr[(*n) + 2];	//세번째char버퍼 0

	*symbol1 = expr[(*n)++];	//첫단어 심볼1
	*symbol2 = 0;	//기본0 심볼2
	*symbol3 = 0;	//기본0 심볼3

	//-가 들어올때
	if (expr_buffer1 == '-' )
	{
		if (isdigit(expr_buffer0) || expr_buffer0 == ')') { // 연산자'-'
			return minus;
		}
		else {						// 부호'-'+ 자리수
			if (isdigit(expr_buffer2)) {	//첫째자리가 숫자라면
				if (isdigit(expr_buffer3)) {	//둘째자리도 숫자라면
					*symbol2 = expr[(*n)++];
					*symbol3 = expr[(*n)++];
					return operand;
				}
				else {						//둘째자리가 숫자가아니면
					*symbol2 = expr[(*n)++];
					return operand;
				}
			}
		}
	}

	//두자리수 양수일때
	if (isdigit(expr_buffer1) && expr_buffer1 !='-') {	//첫번째값이 숫자고 '-'가아니면
		if (isdigit(expr_buffer2)){	//둘째자리수도 양수라면 
			*symbol2 = expr[(*n)++];	//둘째자리수도 기입
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

	default: return operand; //기본값은 피연산자(숫자)
	}
}

void print_token(precedence item) {	//pop과 출력 (바뀐값전달과 delete같이함)
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
	if (*top >= MAX - 1) {				//스택에서 top이 최대치면
		printf("EEROR2 스택이 꽉 찼습니다. 요소 추가가 불가능합니다");
		exit(2);
	}
	stack[++(*top)] = item;	//스택++top에 값 넣기
}

precedence delete_token(int* top) {
	if (*top == -1)
		printf("스택이 비었습니다");
	return stack[(*top)--];
}

void postfix(void)
{
	char symbol;	//첫자리수 받을 변수
	char symbol2;	//두자리수 받을 변수
	char symbol3;	//첫자리가 -라면 두자리까지 받을 변수
	precedence token;
	int n = 0;			//expt n번째

	stack[0] = eos;

	for (token = get_token(&symbol, &symbol2, &symbol3, &n); token != eos; token = get_token(&symbol, &symbol2, &symbol3, &n))
	{	//초기값token = precedence;		token == eos;면끝. token = precedence;다음계산

		if (token == operand) {	// operand피연산자(숫자)가 나오면 바로출력
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
		else if (token == rparen)	//rparen )오른괄호가나오면
		{
			while (stack[top] != lparen)	// laparen'('왼괄호가 나올때까지
				print_token(delete_token(&top));
			delete_token(&top);
		}

		else	//그외에 연산자가 +-/*&\0가 나오면, 스텍에넣고, symbol isp와 token의 icp를 비교 출력
		{
			while (isp[stack[top]] >= icp[token])
				print_token(delete_token(&top));
			add_token(&top, token);
		}
	}
	while ((token = delete_token(&top)) != eos) //token에 eos가들어올때까지 stack에 있는 연산자 다 출력
		print_token(token);
	printf("\n");
}

//postfix함수 안에서 expr안에 방식 //한다음 token = get_token(*symbol,*n);

void read_line(char* input, int len) //중위수식입력함수
{
	int i = 0;

	while (((input[i++] = getchar()) != '\n') && i < len);	//엔터치거나 최대100까지
	input[--i] = '\0';

	if (i >= len) {											//수식 100초과
		printf("EEROR1 수식이 너무 깁니다. MAX=100");
		exit(1);
	}
}
int main(void)
{
	int type;

	read_line(expr, MAX);	//중위수식입력함수

	printf("expr : %s \n", expr);

	postfix();

	printf("expr2 : %s \n", expr2);

	return 0;
}
