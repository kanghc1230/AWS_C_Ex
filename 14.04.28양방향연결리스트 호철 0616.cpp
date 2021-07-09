//연결 리스트 - 큐로 생성 앞으로temp늘려가고 뒤 head쪽부터 삭제
//  dummy-node 생성
//  Queue 초기화 . 자기자신 가리키는
//	가용공간 리스트 avail 만들어서 할 것
#include <stdio.h>
#include <stdlib.h> //exit
struct node {
	struct node* llink;		//node포인터
	int item;
	struct node* rlink;		//node포인터
};
typedef struct node* node_pointer;

struct node* avail;	//가용공간 스트럭쳐 포인터 avail

void addq(struct node*, int);	//addq함수선언
void deleteq(struct node*);		//delete함수선언 //함수 정의할 때 공백 큐 체크 할 것(삭제할 대상이 없습니다)
void listprintq(struct node*); //qlistprint함수 선언
void listfree(struct node*);
node_pointer get_node(node_pointer); //참고용함수
void ret_node(node_pointer);		 //참고용함수
int main()
{
	struct node* head;	//시작위치 스트럭트포인터
	int command;
	int item;

	head = (node*)malloc(sizeof(node));	//head에 더미값
	head->llink = head;	//큐 초기값
	head->rlink = head;

	while (1) {
		printf("1:insert 2:delete 3:output 4:exit \n");
		scanf_s("%d", &command);

		if (command == 1) {	//1:insert
			printf("additem : ");
			scanf_s("%d", &item);
			addq(head, item);
		}
		else if (command == 2) { //2:delete
			if ((head == head->llink) &&(head==head->rlink) ) {
				printf("큐가 비었습니다.\n");
			}
			else {
				deleteq(head);
			}
		}
		else if (command == 3) {
			listprintq(head);
		}
		else if (command == 4) {
			listfree(head);
			break;
		}
		else {	 //command eeror
			printf("command eeror");
			exit(1);
		}

	}
	return 0;
}
void addq(node_pointer head, int item)
{
	/*avail get node*/	
	node_pointer getnode;
	if (avail) {				//avail에 남아있으면 꺼내서쓰고
		getnode = avail;		
		avail = avail->rlink;	//avail이 avail이 가리키는놈 다음놈가리킴
	}
	else {
		getnode = (node*)malloc(sizeof(node));	//없으면 새로 생성
		if (getnode == NULL) {
			printf("메모리꽉참");
			exit(2);
		}
	}
	node_pointer newnode = getnode;	//연결
	//head->llink가 rear역할을 하기에. 맨마지막을 가리킨다.
	newnode->rlink = head;			//newnode가 처음(히드)과 마지막놈(rear)을 가리킴.
	newnode->llink = head->llink;	
	head->llink ->rlink = newnode;	//맨마지막rear의 다음놈(첨이면헤드)이 newnode를 가리킴
	head->llink = newnode;			//맨마지막rear가 newnode를가리킴
	newnode->item = item;
	
}
void deleteq(node_pointer head)
{
	node_pointer deleted;
	deleted = head->rlink;	//deleted가 head다음값 가리키게

	deleted->llink->rlink = deleted->rlink;	//delete 앞놈뒤놈연결 //논리상 끊기 
	deleted->rlink->llink = deleted->llink;

	deleted->rlink = avail;		//avail 담놈 가리키기 (avail에 넣기)	//물리적끊기
	avail = deleted;			//avail 1번타자로 deleted가리키기
}
void listprintq (node_pointer head)
{
	node_pointer search;
	search = head->rlink; //1번부터시작
	while (search != head)	//한바퀴돌아 다시 헤드만날때까지
	{
		printf("search_item : %d \n", search->item);
		search = search->rlink;
	}
}
void listfree(node_pointer head)
{
	node_pointer temp;
	node_pointer search;
	search = head->rlink;	//1번
	while (search != head) {//마지막(처음)번까지
		temp = search->rlink;	//temp는 다음것가리킴 lead역할
		free(search);
		search = temp;	
	}
}



///////////////////필요없는 참고부분///////////////////
node_pointer get_node(void) {
	node_pointer getnode;
	if (avail) {
		getnode = avail;
		avail = avail->llink;
	}
	else {
		getnode = (node*)malloc(sizeof(node));
		if (getnode == NULL) {
			printf("메모리꽉참");
			exit(2);
		}
	}
	return getnode;
}
void ret_node(node_pointer ptr) {
	ptr->rlink = avail;
	avail = ptr;
}
