/*�ǽ�) �־��� ���� ����Ʈ�� ����ȭ ���� �ִ� �Լ� invert(root) �� ����ÿ�.*/
//�Է°� A \n B \n C \n D \n F \n
//��°� ABCDEF ------invert------ FEDCBA
#include<stdio.h>
#include<stdlib.h> //malloc
#include<string.h>
struct node{
	char *name;			//name�� ��°�
	struct node *link;	//��������Ʈ����
};

void listprintf(struct node*);
int getname(char*);
struct node* addlist(char* , struct node*);
char* namecopy(char*);
struct node* invert(struct node*);
int main(void)
{
	struct node *root = NULL; //�Է¹��� ��Ʈ���������� root
	char mainname[20]; 

	/* getchar�޾ƿ��Լ� getname() ĳ������name��ȯ */
	while ( getname(mainname) != EOF )	//getname�� �޾ƿ��°�EOF�鳡	//��EOF�ݺ�Ƚ��
		/* link�������Լ� addlist() ��Ʈ�����ּҹ�ȯ */
		root = addlist(mainname, root); // NULL , char�迭 ����

	/* ����Ʈ����Լ� (��Ʈ���� �����Ͱ� ����Ű�ºκк��� ->���) */
	listprintf(root);

	printf("\n---------invert---------\n");
	/* �ι�Ʈ�Լ� */
	root = invert(root);

	/* ����Ʈ����Լ� */
	listprintf(root); 
	return 0;
}

void listprintf(struct node* p){ //���� ����Ʈ���
	while (p != NULL){
		printf("%s", (*p).name); //p.name ���
		p = p->link;
	}
}

int getname(char* pname)		//mainname�� ������ �����ͺ���pname�� ����
{
	int i = 0;   char c;
	while (((c = getchar()) != '\n') && c != EOF) 		//c�� \n������ �Է°������� 
		*(pname + i++) = c;
	if (c == '\n')
		*(pname + i) = '\0';
	if (c == EOF)
		*pname = EOF;
	return  *pname;	//pname
}
struct node* addlist(char* w , struct node* p)		//mainname, root
{
	if (p == NULL) {	
		p = (struct node*)malloc(sizeof(struct node));	  // �ӽ� �����ͽ�Ʈ����p !�� ��Ʈ���Ĵ�sizeof ����
		p->name = namecopy(w);	//root.name�� ������
		p->link = NULL;
	}
	else
		p->link = addlist(w, p->link);  // ����Լ� w > name  p > root->name
	return  p;
}

char* namecopy(char* s)	//���θ������ node����ü�� name
{
	char* p;  int i = 0;
	p = (char*)malloc(strlen(s) + 1);		//->name�� ũ�� �Ҵ�
	while ((*(p + i) = *(s + i)) != '\0')   //\0���ö����� p������ s���ڿ�
		i++;	
	return  p;	//p�� ����
}

struct node* invert(struct node* lead){			//(����) root�� ����Ű���� lead�� ����Ŵ
	struct node * middle = NULL , * trail;
	while (lead != NULL) {	
		trail = middle;			//lead�ּҰ� ����Ű���� trail�� �Ѱ��� 
		middle = lead;			//lead�� ����Ű���� middle���� �Ѱ���
		lead = middle->link;	//middle->link�� lead���� �Ѱ���
		middle->link = trail;	//middle->link�� trail->name���� ����
	}
	return middle;
}

//invert�Ҵ����� ��-> ����-> ����-> free���ַ��� lead middle ����ּҵ��󰡸鼭 free