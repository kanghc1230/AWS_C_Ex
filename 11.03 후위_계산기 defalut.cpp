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
	//전역변수expr에 메인에서 때려박기 getchar()하고 s[i] = '\0'넣어서 char문장만들고;
	//getop함수 공백제거,엔터제거,숫자, '.'구별 
	//최대글자수나오면 에러처리
	int i=0, c;
	char minus_buffer;

	while ((s[0] = c = getchar()) == ' ' || c == '\t');	//공백이거나 \t면 ' ''\0'내보내기
	s[1] = '\0';
	
	if (!isdigit(c) && c != '.' && c !='-')	//숫자가 아니거나 '.'이아니면. + - / %이면
		return c;

	if (c == '-') {						//c에 -면
		minus_buffer = getchar();		//다음값검사 
		if (isdigit(minus_buffer)) {	// '-','숫자'면 숫자 계속받음
			s[++i] = minus_buffer;
			while (isdigit(s[++i] = c = getchar())); //\0받고 리턴 NUMBER로감
		}
		else {							// '-',' '면 부호니 리턴c
			s[1] = '\0';
			return c;
		}
	}

	if (isdigit(c)) //숫자면
		while (isdigit(s[++i] = c = getchar()))
			;
	if (c == '.')	//'.;이면
		while (isdigit(s[++i] = c = getchar()))
			;
	s[i] = '\0';

	return NUMBER;
}
