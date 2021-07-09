#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;	//������ū
static int icp[] = { 20 ,19 , 12 , 12 , 13 , 13 , 13 , 0 };	//���ؿ� ���Խ� �켱���� �񱳿�
static int isp[] = { 0 , 19 , 12 , 12 , 13 , 13 , 13 , 0 }; //���ؿ� ������ �켱���� �񱳿�

#define MAX 100
#define NUMBER '0'

char expr[MAX];	//�������Ĺ���
precedence stack[MAX]; //������ȯ ���ñ���: enum precedence
int top = 0;		//������ȯstack�� 

char expr2[MAX]; //�������Ĺ���
int expr2_num = 0;

void read_line(char*, int);//�������� �޴��Լ�

precedence get_token(char* symbol1, char* symbol2, char* symbol3, int* n); //precdence�� ã���ִ� �Լ�
void print_token(precedence item); //��������Լ�print_token
void add_token(int* top, precedence item); //�����߰��Լ�add_token
precedence delete_token(int* top); //���û����Լ�delete_token

int getop(char[]);//����Լ�1 getop
void push(double);//��꽺���Լ�2 push
double pop(void); //��꽺���Լ�3 pop

int sp = 0;
double val[MAX];
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*����_���� ��ȯ ������ū �Լ�*/
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
	if (expr_buffer1 == '-')
	{
		if ((*n > 0 && expr_buffer2 == '(') || (isdigit(expr_buffer0) && expr_buffer2 == '('))	 // '������,blank' '-' '(' �� ��ȣ�տ� �����ö�
		{
			expr2[expr2_num++] = '-'; //-(��)������ *-1�� ����. �������Ŀ� �׳� �����
			expr2[expr2_num++] = '1';
			expr2[expr2_num++] = ' ';	
			return times;
		}

		else if (isdigit(expr_buffer0) || expr_buffer0 == ')') { // ������ ���� Ȥ�� ')'�϶� ������'-'
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
	if (isdigit(expr_buffer1) && expr_buffer1 != '-') {	//ù��°���� ���ڰ� '-'���ƴϸ�
		if (isdigit(expr_buffer2)) {	//��°�ڸ����� ������ 
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
	expr2[expr2_num++] = '\n';
}
//postfix�Լ� �ȿ��� expr�ȿ� ��� //�Ѵ��� token = get_token(*symbol,*n);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*����_��� ���� �Լ�*/
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
	int i = 0, c;
	char minus_buffer;

	if (expr2[expr2_num] == 0) {
		return EOF;
	}
	while ((s[0] = c = expr2[expr2_num++]) == ' ' || c == '\t');	//�����̰ų� \t�� ' ''\0'��������
	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-')	//���ڰ� �ƴϰ�&& + - / % \n�̸�
		return c;

	if (c == '-') {						//c�� -��
		minus_buffer = expr2[expr2_num++];		//�������˻� 
		if (isdigit(minus_buffer)) {	// '-','����'�� ���� ��ӹ���
			s[++i] = minus_buffer;
			while (isdigit(s[++i] = c = expr2[expr2_num++]));	//���� NUMBER�ΰ�
		}
		else {							// '-',' '�� ��ȣ�� ����c
			s[1] = '\0';
			return c;
		}
	}

	if (isdigit(c)) //���ڸ�
		while (isdigit(s[++i] = c = expr2[expr2_num++]))
			;
	if (c == '.')	//'.;�̸�
		while (isdigit(s[++i] = c = expr2[expr2_num++]))
			;
	s[i] = '\0';

	return NUMBER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//*�������� �Է��Լ�*/
void read_line(char* input, int len)
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
	read_line(expr, MAX);	//���������Է��Լ�

	printf("�Է°� expr : %s \n", expr);

	postfix();

	printf("������ expr2 : %s \n", expr2);

	int type;
	double op2;
	char s[MAX];

	expr2_num = 0;

	printf("������갪 : ");
	while ((type = getop(s)) != EOF) {	//���� ����
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

