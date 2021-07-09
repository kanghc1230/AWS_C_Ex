/*실습) 주어진 연결 리스트를 역순화 시켜 주는 함수 invert(root) 를 만드시오.*/
//입력값 A \n B \n C \n D \n F \n
//출력값 ABCDEF ------invert------ FEDCBA
#include<stdio.h>
#include<stdlib.h> //malloc
#include<string.h>
struct node{
	char *name;			//name에 출력값
	struct node *link;	//다음리스트연결
};

void listprintf(struct node*);
int getname(char*);
struct node* addlist(char* , struct node*);
char* namecopy(char*);
struct node* invert(struct node*);
int main(void)
{
	struct node *root = NULL; //입력받을 스트럭쳐포인터 root
	char mainname[20]; 

	/* getchar받아올함수 getname() 캐릭터형name반환 */
	while ( getname(mainname) != EOF )	//getname이 받아오는게EOF면끝	//즉EOF반복횟수
		/* link생성할함수 addlist() 스트럭쳐주소반환 */
		root = addlist(mainname, root); // NULL , char배열 전달

	/* 리스트출력함수 (스트럭터 포인터가 가리키는부분부터 ->대로) */
	listprintf(root);

	printf("\n---------invert---------\n");
	/* 인버트함수 */
	root = invert(root);

	/* 리스트출력함수 */
	listprintf(root); 
	return 0;
}

void listprintf(struct node* p){ //연결 리스트출력
	while (p != NULL){
		printf("%s", (*p).name); //p.name 출력
		p = p->link;
	}
}

int getname(char* pname)		//mainname을 가져와 포인터변수pname이 받음
{
	int i = 0;   char c;
	while (((c = getchar()) != '\n') && c != EOF) 		//c에 \n전까지 입력값들전달 
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
		p = (struct node*)malloc(sizeof(struct node));	  // 임시 포인터스트럭쳐p !꼭 스트럭쳐는sizeof 연산
		p->name = namecopy(w);	//root.name에 값들어가고
		p->link = NULL;
	}
	else
		p->link = addlist(w, p->link);  // 재귀함수 w > name  p > root->name
	return  p;
}

char* namecopy(char* s)	//새로만들어진 node구조체의 name
{
	char* p;  int i = 0;
	p = (char*)malloc(strlen(s) + 1);		//->name의 크기 할당
	while ((*(p + i) = *(s + i)) != '\0')   //\0나올때까지 p에복사 s문자열
		i++;	
	return  p;	//p에 저장
}

struct node* invert(struct node* lead){			//(인자) root가 가리키던걸 lead가 가리킴
	struct node * middle = NULL , * trail;
	while (lead != NULL) {	
		trail = middle;			//lead주소가 가리키던걸 trail로 넘겨줌 
		middle = lead;			//lead가 가리키던걸 middle에게 넘겨줌
		lead = middle->link;	//middle->link를 lead에게 넘겨줌
		middle->link = trail;	//middle->link를 trail->name으로 연결
	}
	return middle;
}

//invert할당응용 ㅁ-> ㅁㅁ-> ㅁㅁ-> free해주려면 lead middle 계속주소따라가면서 free