#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define max_size 250

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand   //lparen=0, rparen=1, plus=2, minus=3, times=4, divide=5, mod=6, eos=7, oper=8
}precedence;
static int icp[] = { 20,19,12,12,13,13,13,0 };
static int isp[] = { 0,19,12,12,13,13,13,0 };

float stack_op[max_size];					    //숫자 넣는 스텍
char stack_post[max_size];					    //연산기호 넣는 스텍
int size;									    //후위표기로 변환되어지는 식 길이파악(계산 시 문자열로 읽어들여 변환하기 위해 맨 뒤에 '\0'값 삽입을 위해
int top;
//함수 선언
char* postfix(char*);							//중위표현식 후위표현식으로
precedence get_token(char*, char*, int*);		//토큰 값 반환
void post_push(precedence);						//연산기호 스텍에 넣는 함수
precedence post_pop(void);						//스텍에서 연산기호 빼는 함수
char tokentochar(precedence);					//precedence 변수를 char형태로 변환
float op_pop(void);								//후위표현식 계산할 때 숫자 넣는 스텍
void op_push(float);							//숫자 뺴는 스텍 함수
float op_op(char);								//들어온 연산기호에 맞는 계산하여 값 반환

int main(void) {
	int i = 0, j = 0;
	char c;
	char anum[10];
	char* expr = (char*)malloc(sizeof(char) * 100);
	float result = 0.0;

	while ((c = getchar()) != '\n') {			//수식입력
		if (c == '(') {							//'('가 입력으로 들어오는 경우 괄호 앞에는 1*가 있는 것으로 간주
			*(expr + i++) = '1';				//괄호앞에 -가 있는 경우 처리해주기 위해
			*(expr + i++) = '*';
		}

		*(expr + i++) = c;
	}

	*(expr + i) = '\0';						    //문자열의 맨 뒤에 널값 삽입
	expr = postfix(expr);				        //후위표현식 변환 함수 호출	

	for (i = 0; i < strlen(expr); i++) {					//후위표현식의 길이 만큼 반복문 진행
		if ((isdigit(expr[i]) != 0) || (expr[i] == '.')) {  //현재의 expr 값이 숫자이거나 . 인경우
			anum[j++] = expr[i];							//anum 배열에다가 입력
		}
		else if (expr[i] == 'b') {							//b는 -값으로 변환
			anum[j++] = '-';
		}
		else if (expr[i] == 'a') {							//a의 경우 문자열에서 숫자의 길이를 구분하기 위해 삽입한 것이므로
			anum[j] = '\0';									//anum배열의 맨뒤에 널값을 넣어준 후
			if (j != 0) {									//j=0인 경우 숫자가 anum배열의 없다는 것을 뜻하므로 조건식을 !=0 으로 set
				op_push(atof(anum));						//anum배열의 값을 atof한후 스텍에 넣어줌
			}
			j = 0;											//j=0으로 초기화하여 다시 숫자가 들어올경우 anum배열의 0부터 넣어주기 위해
		}
		else if (isdigit(expr[i]) == 0) {					//현재의 expr값이 연산기호인 경우
			anum[j] = '\0';									//a가 아닌 연산기호를 만나도 숫자의 길이끝으로 간주하고
			if (j != 0)										//atof를 한후 스텍에 넣어줌
				op_push(atof(anum));
			j = 0;
			op_push(op_op(expr[i]));						//현재의 exrp의 연산기호값에 따른 op_op함수에서 계산후 다시 스텍이 넣어줌
		}
		else
			continue;
	}
	result = op_pop();										//마지막에 스텍에 들어있는 값 결과값에 넣어줌
	printf("%f\n", result);
	return 0;
}
char* postfix(char* expr) {
	char symbol;
	precedence token;
	int n = 0;
	static char post[max_size];				       //후위표기로 변환되어지는 식 넣을 배열 함수가 종료된 후에도 메모리를 유지하기 위해 static으로 선언

	stack_post[0] = eos;

	for (token = get_token(expr, &symbol, &n); token != eos; token = get_token(expr, &symbol, &n)) {
		if (token == operand)						//get_token으로 얻은 현재 token값이 숫자인 경우
			post[size++] = symbol;					//후위표기식 배열에다가 바로 넣어줌
		else if (token == rparen) {					//오른쪽 괄호를 만난 경우
			while (stack_post[top] != lparen)		//왼쪽 괄호를 만날떄까지
				post[size++] = tokentochar(post_pop()); //식 배열에 연산기호를 넣어줌
			post_pop();								//왼쪽 괄호 삭제
		}
		else {
			if (token == minus) {					//현재 token값이 '-'인 경우
				if (size == 0) {					//식의 맨 처음에서 발견된 경우
					post[size++] = 'b';				//'-'를 'b'로 치환하여 후위표기식 배열에 바로 넣어줌
				}
				else if ((isdigit(expr[n - 2]) == 0) && expr[n - 2] != ')') {   //연산기호 바로 뒤에 나오는 '-'의 경우에도 연산기호가 아닌 부호값이므로
					post[size++] = 'b';									  //후위표기식 배열에 넣어줌( ')'의 뒤에 있는 '-'의 경우 연산기호이므로 예외처리
				}
				else {													  //**중위표기식에서 연산기호를 만나는 순간이 하나의 오퍼랜드 숫자의 길이끝이므로 구분하기 위해 'a'를 넣어줌
					post[size++] = 'a';									  //연산기호 '-'인 경우 숫자의 끝(2자리수 이상인지 구분하기 위해) 'a'를 넣어줌
					while (isp[stack_post[top]] >= icp[token])		   	  //연산기호 우선순위를 비교하여
						post[size++] = tokentochar(post_pop());			  //현재의 token값의 우선순위가 스텍상단에 있는 연산기호보다 낮을경우 스텍에서 빼줌
					post_push(token);											  //현재의 token값 스텍에 넣어줌
				}
			}
			else {									            //'-'가 아닌 문자가 들어온 경우에도
				post[size++] = 'a';								//연산기호 '-'가 들어왔을 때와 똑같이 처리
				while (isp[stack_post[top]] >= icp[token])
					post[size++] = tokentochar(post_pop());
				post_push(token);
			}
		}
	}
	while ((token = post_pop()) != eos)							//for문이 종료된후 스텍에 남아있는 연산기호들을
		post[size++] = tokentochar(token);						//후위표기식 배열에 넣어줌
	return post;												//후위표기식 배열의 주소값 리턴
}

precedence get_token(char* expr, char* symbol, int* n) {	    //현재의 symobl값에 따라 precedence형으로 변환하여 반환
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(':return lparen;
	case ')':return rparen;
	case '+':return plus;
	case '-':return minus;
	case '/':return divide;
	case '*':return times;
	case '%':return mod;
	case '\0':return eos;

	default:return operand;
	}
}
char tokentochar(precedence symbol) {						  //precedence로 변환된 symbol값을 다시 원래의 문자값으로 변환 후 반환
	switch (symbol) {
	case lparen:return '(';
	case rparen:return ')';
	case plus:return '+';
	case minus:return '-';
	case divide:return '/';
	case times:return '*';
	case mod:return '%';
	}
}

precedence post_pop(void) {									  //연산기호 스텍의 값 반환(pop)
	if (top < 0) {
		printf("Stack is Empty exit\n");
		exit(1);
	}

	return stack_post[top--];
}
void post_push(precedence symbol) {								  //연산기호 스택의 값 추가(push)
	if (top > max_size) {
		printf("Stack if full exit\n");
		exit(1);
	}
	stack_post[++top] = symbol;
}

float op_pop(void) {									      //숫자 스택의 값 반환(pop)
	if (top < 0) {
		printf("Stack is Empty exit\n");
		exit(1);
	}
	return stack_op[top--];
}
void op_push(float num) {									 //숫자 스텍의 값 추가(push)
	if (top > max_size) {
		printf("Stack if full exit\n");
		exit(1);
	}
	stack_op[++top] = num;
}
float op_op(char op) {
	float a;
	a = op_pop();											//연산기호의 경우 숫자의 순서가 관련이 있는 경우가 존재
	switch (op) {											//'a'로 식의 뒤에있는 숫자를 먼저 pop하여 받음
	case '+':return op_pop() + a;							//연산기호에 따른 계산 실행 후 결과값 pop
	case '-':return op_pop() - a;
	case '/':return op_pop() / a;
	case '*':return op_pop() * a;
	case '%':return (int)op_pop() % (int)a;
	}
}