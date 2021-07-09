// 
/*중위표기-> 후위표기 계산기
  1)피연산자가 나오면 바로출력
  2) 연산자가 들어오면 자기보다 우선순위가 높거나 같은 것들을 빼고, 낮은것을 자신을 스택에 담는다.
  3) 여는 괄호 '('를 만나면 무조건 스택에 담는다.
  4) 닫는 괄호 ')'를 만나면 '('를 만날 때까지 스택에서 출력한다.
  */

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
typedef enum { lparen , rparen , plus , minus , times , divide , mod , eos , operand }precedence;	//연산토큰
static int icp[] = { 20 ,19 , 12 , 12 , 13 , 13 , 13 , 0 };	//스텍에 진입시 우선순위 비교용
static int isp[] = { 0 , 19 , 12 , 12 , 13 , 13 , 13 , 0 }; //스텍에 있을때 우선순위 비교용
#define MAX 100
#define NUMBER '0'

char expr[MAX];	//중위수식받음
precedence stack[MAX]; //스택구조: enum precedence
int top = 0;		//expr스텍의위치

char expr2[MAX]; //후위수식받음
int expr2_num = 0;

precedence get_token(char *symbol, int *n)	//인자(symbol포인터, n번째값작동중)  precdence를 찾아주는 함수
{
	*symbol = expr[(*n)++];		// 문자배열[n++]값을 symbol에 넣고
	switch (*symbol) {
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
	switch (item) {
	case 2:
		printf("+"); expr2[expr2_num++] = '+'; expr2[expr2_num++] = ' '; break;
	case 3:
		printf("-"); expr2[expr2_num++] = '-'; expr2[expr2_num++] = ' '; break;
	case 4:
		printf("*"); expr2[expr2_num++] = '*'; expr2[expr2_num++] = ' '; break;
	case 5:
		printf("/"); expr2[expr2_num++] = '/'; expr2[expr2_num++] = ' '; break;
	case 6:
		printf("%"); expr2[expr2_num++] = '%'; expr2[expr2_num++] = ' '; break;
	}	
}
void add_token(int *top, precedence item) {
	if (*top >= MAX - 1) {				//스택에서 top이 최대치면
		printf( "EEROR2 스택이 꽉 찼습니다. 요소 추가가 불가능합니다");
		exit(2);
	}
	stack[++(*top)] = item;	//스택++top에 값 넣기
}

precedence delete_token(int *top) {
	if (*top == -1)
		printf("스택이 비었습니다");
	return stack[(*top)--];
}

void postfix(void)
{
	char symbol;
	precedence token;
	int n = 0;			//expt n번째

	stack[0] = eos;

	for (token = get_token(&symbol, &n); token != eos; token = get_token(&symbol, &n))
	{	//초기값token = precedence;		token == eos;면끝. token = precedence;다음계산

		if (token == operand) {	// operand피연산자(숫자)가 나오면 바로출력
			printf("%c", symbol);
			expr2[expr2_num++] = symbol;
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

	if (i >= len){											//수식 100초과
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

