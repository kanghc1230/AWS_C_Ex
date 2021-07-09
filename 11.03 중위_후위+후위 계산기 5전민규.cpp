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

float stack_op[max_size];					    //���� �ִ� ����
char stack_post[max_size];					    //�����ȣ �ִ� ����
int size;									    //����ǥ��� ��ȯ�Ǿ����� �� �����ľ�(��� �� ���ڿ��� �о�鿩 ��ȯ�ϱ� ���� �� �ڿ� '\0'�� ������ ����
int top;
//�Լ� ����
char* postfix(char*);							//����ǥ���� ����ǥ��������
precedence get_token(char*, char*, int*);		//��ū �� ��ȯ
void post_push(precedence);						//�����ȣ ���ؿ� �ִ� �Լ�
precedence post_pop(void);						//���ؿ��� �����ȣ ���� �Լ�
char tokentochar(precedence);					//precedence ������ char���·� ��ȯ
float op_pop(void);								//����ǥ���� ����� �� ���� �ִ� ����
void op_push(float);							//���� ���� ���� �Լ�
float op_op(char);								//���� �����ȣ�� �´� ����Ͽ� �� ��ȯ

int main(void) {
	int i = 0, j = 0;
	char c;
	char anum[10];
	char* expr = (char*)malloc(sizeof(char) * 100);
	float result = 0.0;

	while ((c = getchar()) != '\n') {			//�����Է�
		if (c == '(') {							//'('�� �Է����� ������ ��� ��ȣ �տ��� 1*�� �ִ� ������ ����
			*(expr + i++) = '1';				//��ȣ�տ� -�� �ִ� ��� ó�����ֱ� ����
			*(expr + i++) = '*';
		}

		*(expr + i++) = c;
	}

	*(expr + i) = '\0';						    //���ڿ��� �� �ڿ� �ΰ� ����
	expr = postfix(expr);				        //����ǥ���� ��ȯ �Լ� ȣ��	

	for (i = 0; i < strlen(expr); i++) {					//����ǥ������ ���� ��ŭ �ݺ��� ����
		if ((isdigit(expr[i]) != 0) || (expr[i] == '.')) {  //������ expr ���� �����̰ų� . �ΰ��
			anum[j++] = expr[i];							//anum �迭���ٰ� �Է�
		}
		else if (expr[i] == 'b') {							//b�� -������ ��ȯ
			anum[j++] = '-';
		}
		else if (expr[i] == 'a') {							//a�� ��� ���ڿ����� ������ ���̸� �����ϱ� ���� ������ ���̹Ƿ�
			anum[j] = '\0';									//anum�迭�� �ǵڿ� �ΰ��� �־��� ��
			if (j != 0) {									//j=0�� ��� ���ڰ� anum�迭�� ���ٴ� ���� ���ϹǷ� ���ǽ��� !=0 ���� set
				op_push(atof(anum));						//anum�迭�� ���� atof���� ���ؿ� �־���
			}
			j = 0;											//j=0���� �ʱ�ȭ�Ͽ� �ٽ� ���ڰ� ���ð�� anum�迭�� 0���� �־��ֱ� ����
		}
		else if (isdigit(expr[i]) == 0) {					//������ expr���� �����ȣ�� ���
			anum[j] = '\0';									//a�� �ƴ� �����ȣ�� ������ ������ ���̳����� �����ϰ�
			if (j != 0)										//atof�� ���� ���ؿ� �־���
				op_push(atof(anum));
			j = 0;
			op_push(op_op(expr[i]));						//������ exrp�� �����ȣ���� ���� op_op�Լ����� ����� �ٽ� ������ �־���
		}
		else
			continue;
	}
	result = op_pop();										//�������� ���ؿ� ����ִ� �� ������� �־���
	printf("%f\n", result);
	return 0;
}
char* postfix(char* expr) {
	char symbol;
	precedence token;
	int n = 0;
	static char post[max_size];				       //����ǥ��� ��ȯ�Ǿ����� �� ���� �迭 �Լ��� ����� �Ŀ��� �޸𸮸� �����ϱ� ���� static���� ����

	stack_post[0] = eos;

	for (token = get_token(expr, &symbol, &n); token != eos; token = get_token(expr, &symbol, &n)) {
		if (token == operand)						//get_token���� ���� ���� token���� ������ ���
			post[size++] = symbol;					//����ǥ��� �迭���ٰ� �ٷ� �־���
		else if (token == rparen) {					//������ ��ȣ�� ���� ���
			while (stack_post[top] != lparen)		//���� ��ȣ�� ����������
				post[size++] = tokentochar(post_pop()); //�� �迭�� �����ȣ�� �־���
			post_pop();								//���� ��ȣ ����
		}
		else {
			if (token == minus) {					//���� token���� '-'�� ���
				if (size == 0) {					//���� �� ó������ �߰ߵ� ���
					post[size++] = 'b';				//'-'�� 'b'�� ġȯ�Ͽ� ����ǥ��� �迭�� �ٷ� �־���
				}
				else if ((isdigit(expr[n - 2]) == 0) && expr[n - 2] != ')') {   //�����ȣ �ٷ� �ڿ� ������ '-'�� ��쿡�� �����ȣ�� �ƴ� ��ȣ���̹Ƿ�
					post[size++] = 'b';									  //����ǥ��� �迭�� �־���( ')'�� �ڿ� �ִ� '-'�� ��� �����ȣ�̹Ƿ� ����ó��
				}
				else {													  //**����ǥ��Ŀ��� �����ȣ�� ������ ������ �ϳ��� ���۷��� ������ ���̳��̹Ƿ� �����ϱ� ���� 'a'�� �־���
					post[size++] = 'a';									  //�����ȣ '-'�� ��� ������ ��(2�ڸ��� �̻����� �����ϱ� ����) 'a'�� �־���
					while (isp[stack_post[top]] >= icp[token])		   	  //�����ȣ �켱������ ���Ͽ�
						post[size++] = tokentochar(post_pop());			  //������ token���� �켱������ ���ػ�ܿ� �ִ� �����ȣ���� ������� ���ؿ��� ����
					post_push(token);											  //������ token�� ���ؿ� �־���
				}
			}
			else {									            //'-'�� �ƴ� ���ڰ� ���� ��쿡��
				post[size++] = 'a';								//�����ȣ '-'�� ������ ���� �Ȱ��� ó��
				while (isp[stack_post[top]] >= icp[token])
					post[size++] = tokentochar(post_pop());
				post_push(token);
			}
		}
	}
	while ((token = post_pop()) != eos)							//for���� ������� ���ؿ� �����ִ� �����ȣ����
		post[size++] = tokentochar(token);						//����ǥ��� �迭�� �־���
	return post;												//����ǥ��� �迭�� �ּҰ� ����
}

precedence get_token(char* expr, char* symbol, int* n) {	    //������ symobl���� ���� precedence������ ��ȯ�Ͽ� ��ȯ
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
char tokentochar(precedence symbol) {						  //precedence�� ��ȯ�� symbol���� �ٽ� ������ ���ڰ����� ��ȯ �� ��ȯ
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

precedence post_pop(void) {									  //�����ȣ ������ �� ��ȯ(pop)
	if (top < 0) {
		printf("Stack is Empty exit\n");
		exit(1);
	}

	return stack_post[top--];
}
void post_push(precedence symbol) {								  //�����ȣ ������ �� �߰�(push)
	if (top > max_size) {
		printf("Stack if full exit\n");
		exit(1);
	}
	stack_post[++top] = symbol;
}

float op_pop(void) {									      //���� ������ �� ��ȯ(pop)
	if (top < 0) {
		printf("Stack is Empty exit\n");
		exit(1);
	}
	return stack_op[top--];
}
void op_push(float num) {									 //���� ������ �� �߰�(push)
	if (top > max_size) {
		printf("Stack if full exit\n");
		exit(1);
	}
	stack_op[++top] = num;
}
float op_op(char op) {
	float a;
	a = op_pop();											//�����ȣ�� ��� ������ ������ ������ �ִ� ��찡 ����
	switch (op) {											//'a'�� ���� �ڿ��ִ� ���ڸ� ���� pop�Ͽ� ����
	case '+':return op_pop() + a;							//�����ȣ�� ���� ��� ���� �� ����� pop
	case '-':return op_pop() - a;
	case '/':return op_pop() / a;
	case '*':return op_pop() * a;
	case '%':return (int)op_pop() % (int)a;
	}
}