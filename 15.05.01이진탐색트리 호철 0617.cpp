#include<stdio.h>
#include<stdlib.h> //exit
//이진탐색트리 왼쪽은 작은값 오른쪽은 큰값이 나오게 배치하는 이진트리
struct tnode {
	int item;
	struct tnode* left;
	struct tnode* right;
};

struct tnode* addtree(struct tnode*,int);	//addtree함수 선언
void deletetree(struct tnode**, int);		//deletetree함수 선언
void treeprint(struct tnode*);				//treeprint함수 선언

int main(void)
{
	struct tnode* root;	
	int command;	//명령 받을 변수
	int item;		//삽입,삭제 값 받을 변수
	root = NULL;	//스트럭쳐포인터 첫값 작동되도록 NULL로 초기화

	while (1) {
		printf("\n이진트리구조 ( 1:삽입  2:삭제  3:출력 4:종료 ) \n입력 : ");
		scanf("%d", &command);
		
		if (command == 1) {		
			printf("추가할 item : ");
			scanf("%d", &item);
			root = addtree(root, item);
		}
		else if (command == 2) {
			printf("삭제할 item : ");
			scanf("%d", &item);
			deletetree(&root, item);	//더블포인터,삭제할값
		}
		else if (command == 3) {
			treeprint(root);
			printf("\n");
		}
		else if (command == 4)
			break;
		else {
			printf("\nCommand error\n");
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
		printf(" ERROR : 이미 존재하는 숫자입니다. \n\n");
	else if (num < (p->item))	//들어온값이 기준parent보다 작으면
		p->left = addtree(p->left, num);	//왼쪽에 주소값 = 재귀(왼쪽주소값, 입력값) 
	else if (num > (p->item))
		p->right = addtree(p->right, num);	//오른쪽 주소값 = 재귀(오른쪽주소값, 입력값) 

	return p;
}

/*딜리트함수 deletetree정의*/
void deletetree(struct tnode** root, int num) {		//인자(스트럭쳐 이중포인터, 삭제할값)
	struct tnode *deleted, *prev, *parent, *move;	//prev는 delete의부모. parent는 move의 부모. move이동할대상. 
	deleted = prev = parent = move = NULL;		//초기화

	//num을 근거로 삭제할 deleted 위치 추적
	deleted = *root;
	while (deleted) {				//1이면 
		if (num == deleted->item)
			break;
		else if (num < deleted->item) {		//num보다 작으면 delete 왼쪽이동
			prev = deleted;
			deleted = deleted->left;
		}
		else { //(num > deleted->item)		//num보다 크면 delete 오른쪽이동
			prev = deleted;
			deleted = deleted->right;
		}
	}
	/* 값이없으면 돌아가기 */
	if (deleted == NULL) {	//삭제할값이 존재하지 않으면
		printf(" ERROR : 존재하지 않는 값으로 삭제할 수 없습니다.\n\n");
		return;	//되돌아가기
	}

	/* 값이 있으면 삭제 */
	if (deleted->left) {		//왼쪽서브 트리에서 조정 하는 경우
		parent = deleted;		//parent초기값
		move = deleted->left;	//move 딜리트왼쪽 초기값
		//무브위치추적
		while (move->right != NULL)	//move의 오른쪽. 즉 제일 큰값을 찾아움직임.
		{
			parent = move;
			move = move->right;
		}

		//2번케이스 대각선형태. parent==delete, 왼쪽의최대인 move에게 왼쪽노드가 있었을경우
		if (parent == deleted)	
			parent->left = move->left;
		//1번케이스 : 왼쪽의최대인 move에게 왼쪽노드가 있었을경우 ( 양쪽 다 널이어도 널로 이어져 상관없다 )
		parent->right = move->left;

		deleted->item = move->item;
		free(move);
	}

	else  if (deleted->right) {	// 오른쪽 서브 트리에서 조정
		parent = deleted;		//parent초기값
		move = deleted->right;	//move 딜리트오른쪽 초기값
		//무브위치추적
		while (move->left != NULL) //move의 왼쪽. 즉 제일 작은값을 찾아움직임.
		{
			parent = move;
			move = move->left;
		}
		if (parent == deleted)		
			parent->right = move->right; 
					
		parent->left = move->right;

		deleted->item = move->item;
		free(move);
	}


	//3번케이스 : 단말노드의 삭제후 NULL직접넣기 (즉 delete 삭제대상의 자식이 없으면)
	else  if (prev == NULL) {  // 마지막으로 하나 남은 노드 삭제 일 경우 
		free(deleted);
		*root = NULL;    // 공백 트리가 되었음을 알려 주는 부분 
	}
	else if (deleted == prev->left) {  // 왼쪽 단말 노드 삭제일 경우
		prev->left = NULL;
		free(deleted);
	}
	else  if (deleted == prev->right) { // 오른쪽 단말 노드 삭제일 경우
		prev->right = NULL;
		free(deleted);
	}
}

/*출력함수 treeprint정의*/
void treeprint(struct tnode* p) {	//중위탐색 출력
	if (p != NULL) {
		treeprint(p->left);
		printf(" %d ", p->item);
		treeprint(p->right);
	}
}
