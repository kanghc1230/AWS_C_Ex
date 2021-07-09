#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;	//연산토큰
static int icp[] = { 20 ,19 , 12 , 12 , 13 , 13 , 13 , 0 };	//스텍에 진입시 우선순위 비교용
static int isp[] = { 0 , 19 , 12 , 12 , 13 , 13 , 13 , 0 }; //스텍에 있을때 우선순위 비교용

#define MAX 100
#define NUMBER '0'

char expr[MAX];	//중위수식받음
precedence stack[MAX]; //후위변환 스택구조: enum precedence
int top = 0;		//후위변환stack의 

char expr2[MAX]; //후위수식받음
int expr2_num = 0;

void read_line(char*, int);//중위수식 받는함수

precedence get_token(char* symbol1, char* symbol2, char* symbol3, int* n); //precdence를 찾아주는 함수
void print_token(precedence item); //스택출력함수print_token
void add_token(int* top, precedence item); //스택추가함수add_token
precedence delete_token(int* top); //스택삭제함수delete_token

int getop(char[]);//계산함수1 getop
void push(double);//계산스텍함수2 push
double pop(void); //계산스텍함수3 pop

int sp = 0;
double val[MAX];
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*중위_후위 변환 스택토큰 함수*/
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
	if (expr_buffer1 == '-')
	{
		if ((*n > 0 && expr_buffer2 == '(') || (isdigit(expr_buffer0) && expr_buffer2 == '('))	 // '연산자,blank' '-' '(' 즉 괄호앞에 음수올때
		{
			expr2[expr2_num++] = '-'; //-(ㅁ)수식은 *-1과 같음. 후위수식에 그냥 덮어쓰기
			expr2[expr2_num++] = '1';
			expr2[expr2_num++] = ' ';	
			return times;
		}

		else if (isdigit(expr_buffer0) || expr_buffer0 == ')') { // 전값이 정수 혹은 ')'일때 연산자'-'
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
	if (isdigit(expr_buffer1) && expr_buffer1 != '-') {	//첫번째값이 숫자고 '-'가아니면
		if (isdigit(expr_buffer2)) {	//둘째자리수도 양수라면 
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
	expr2[expr2_num++] = '\n';
}
//postfix함수 안에서 expr안에 방식 //한다음 token = get_token(*symbol,*n);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*후위_계산 스택 함수*/
void push(double f)
{
	if (sp < MAX)
		val[sp++] = f;
	else
		printf("error 스텍이 꽉차서 넣을수없습니다.");
}

double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error3 스택이 비었습니다");
		return 0.0;
	}
}
//후위표현을 받는 함수. 수식받아서 계산하기전 전달하는 gettop
int getop(char s[]) {
	int i = 0, c;
	char minus_buffer;

	if (expr2[expr2_num] == 0) {
		return EOF;
	}
	while ((s[0] = c = expr2[expr2_num++]) == ' ' || c == '\t');	//공백이거나 \t면 ' ''\0'내보내기
	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-')	//숫자가 아니고&& + - / % \n이면
		return c;

	if (c == '-') {						//c에 -면
		minus_buffer = expr2[expr2_num++];		//다음값검사 
		if (isdigit(minus_buffer)) {	// '-','숫자'면 숫자 계속받음
			s[++i] = minus_buffer;
			while (isdigit(s[++i] = c = expr2[expr2_num++]));	//리턴 NUMBER로감
		}
		else {							// '-',' '면 부호니 리턴c
			s[1] = '\0';
			return c;
		}
	}

	if (isdigit(c)) //숫자면
		while (isdigit(s[++i] = c = expr2[expr2_num++]))
			;
	if (c == '.')	//'.;이면
		while (isdigit(s[++i] = c = expr2[expr2_num++]))
			;
	s[i] = '\0';

	return NUMBER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//*중위수식 입력함수*/
void read_line(char* input, int len)
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
	read_line(expr, MAX);	//중위수식입력함수

	printf("입력값 expr : %s \n", expr);

	postfix();

	printf("후위값 expr2 : %s \n", expr2);

	int type;
	double op2;
	char s[MAX];

	expr2_num = 0;

	printf("후위계산값 : ");
	while ((type = getop(s)) != EOF) {	//후위 계산기
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
				printf("error 0을 나눌수없습니다.");
			break;
		case '\n':
			printf("\t%.8g \n", pop());
			break;
		default:
			printf("error 알수없는 명령어");
			break;
		}
	}
	return 0;
}

