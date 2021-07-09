#include<stdio.h>
#include<stdlib.h> //exit
struct tnode {
	int item;
	struct tnode* left;
	struct tnode* right;
};

struct tnode* addtree(struct tnode*, int);	//addtree함수 선언
//void deletetree();						//deletetree함수 선언
void treeprint(struct tnode*);				//treeprint함수 선언

int main(void)
{
	struct tnode* root;
	int command;	//명령 받을 변수
	int item;		//삽입 값 받을 변수
	root = NULL;	//스트럭쳐포인터 첫값 작동되도록 NULL로 초기화

	while (1) {
		printf("트리구조 ( 1:삽입  2:삭제  3:출력 4:종료 ) \n입력 : ");
		scanf("%d", &command);

		if (command == 1) {
			printf("add item : ");
			scanf("%d", &item);
			root = addtree(root, item);
		}
		else if (command == 2) {
			//삭제함수
		}
		else if (command == 3) {
			treeprint(root);
		}
		else if (command == 4)
			break;
		else {
			printf("command error");
			exit(1);
		}
	}
	return 0;
}

/*삽입함수 addtree정의*/
struct tnode* addtree(struct tnode* p, int num) {	//인자로(기준포인터, 입력값)을 받아 트리를 생성하고 포인터p를 리턴	
	if (p == NULL)				//p가 가르키는게 없으면 생성 ex루트
	{
		p = (struct tnode*)malloc(sizeof(tnode));
		p->item = num;
		p->left = NULL;			//생성후NULL초기화
		p->right = NULL;
	}
	else if (num == p->item)	//p가 가르키는게 있으면
		printf("존재하는 숫자입니다. \n");
	else if (num < (p->item))	//들어온값이 기준parent보다 작으면
		p->left = addtree(p->left, num);	//왼쪽에 주소값 = 재귀(왼쪽주소값, 입력값) 
	else if (num > (p->item))
		p->right = addtree(p->right, num);	//오른쪽 주소값 = 재귀(오른쪽주소값, 입력값) 

	return p;
}

/*딜리트함수 deletetree정의*/

/*출력함수 treeprint정의*/
void treeprint(struct tnode* p) {	//중위탐색 출력
	if (p != NULL) {
		treeprint(p->left);
		printf("%d\n", p->item);
		treeprint(p->right);
	}
}