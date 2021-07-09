//���� ����Ʈ - ť�� ���� ������temp�÷����� �� head�ʺ��� ����
//  dummy-node ����
//  Queue �ʱ�ȭ . �ڱ��ڽ� ����Ű��
//	������� ����Ʈ avail ���� �� ��
#include <stdio.h>
#include <stdlib.h> //exit
struct node {
	struct node* llink;		//node������
	int item;
	struct node* rlink;		//node������
};
typedef struct node* node_pointer;

struct node* avail;	//������� ��Ʈ���� ������ avail

void addq(struct node*, int);	//addq�Լ�����
void deleteq(struct node*);		//delete�Լ����� //�Լ� ������ �� ���� ť üũ �� ��(������ ����� �����ϴ�)
void listprintq(struct node*); //qlistprint�Լ� ����
void listfree(struct node*);
node_pointer get_node(node_pointer); //������Լ�
void ret_node(node_pointer);		 //������Լ�
int main()
{
	struct node* head;	//������ġ ��Ʈ��Ʈ������
	int command;
	int item;

	head = (node*)malloc(sizeof(node));	//head�� ���̰�
	head->llink = head;	//ť �ʱⰪ
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
				printf("ť�� ������ϴ�.\n");
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
	if (avail) {				//avail�� ���������� ����������
		getnode = avail;		
		avail = avail->rlink;	//avail�� avail�� ����Ű�³� �����𰡸�Ŵ
	}
	else {
		getnode = (node*)malloc(sizeof(node));	//������ ���� ����
		if (getnode == NULL) {
			printf("�޸𸮲���");
			exit(2);
		}
	}
	node_pointer newnode = getnode;	//����
	//head->llink�� rear������ �ϱ⿡. �Ǹ������� ����Ų��.
	newnode->rlink = head;			//newnode�� ó��(����)�� ��������(rear)�� ����Ŵ.
	newnode->llink = head->llink;	
	head->llink ->rlink = newnode;	//�Ǹ�����rear�� ������(÷�̸����)�� newnode�� ����Ŵ
	head->llink = newnode;			//�Ǹ�����rear�� newnode������Ŵ
	newnode->item = item;
	
}
void deleteq(node_pointer head)
{
	node_pointer deleted;
	deleted = head->rlink;	//deleted�� head������ ����Ű��

	deleted->llink->rlink = deleted->rlink;	//delete �ճ�ڳ𿬰� //���� ���� 
	deleted->rlink->llink = deleted->llink;

	deleted->rlink = avail;		//avail ��� ����Ű�� (avail�� �ֱ�)	//����������
	avail = deleted;			//avail 1��Ÿ�ڷ� deleted����Ű��
}
void listprintq (node_pointer head)
{
	node_pointer search;
	search = head->rlink; //1�����ͽ���
	while (search != head)	//�ѹ������� �ٽ� ��常��������
	{
		printf("search_item : %d \n", search->item);
		search = search->rlink;
	}
}
void listfree(node_pointer head)
{
	node_pointer temp;
	node_pointer search;
	search = head->rlink;	//1��
	while (search != head) {//������(ó��)������
		temp = search->rlink;	//temp�� �����Ͱ���Ŵ lead����
		free(search);
		search = temp;	
	}
}



///////////////////�ʿ���� ����κ�///////////////////
node_pointer get_node(void) {
	node_pointer getnode;
	if (avail) {
		getnode = avail;
		avail = avail->llink;
	}
	else {
		getnode = (node*)malloc(sizeof(node));
		if (getnode == NULL) {
			printf("�޸𸮲���");
			exit(2);
		}
	}
	return getnode;
}
void ret_node(node_pointer ptr) {
	ptr->rlink = avail;
	avail = ptr;
}
