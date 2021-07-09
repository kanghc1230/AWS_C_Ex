#include<stdio.h>
#include<stdlib.h> //exit
struct tnode {
	int item;
	struct tnode* left;
	struct tnode* right;
};

struct tnode* addtree(struct tnode*, int);	//addtree�Լ� ����
//void deletetree();						//deletetree�Լ� ����
void treeprint(struct tnode*);				//treeprint�Լ� ����

int main(void)
{
	struct tnode* root;
	int command;	//��� ���� ����
	int item;		//���� �� ���� ����
	root = NULL;	//��Ʈ���������� ù�� �۵��ǵ��� NULL�� �ʱ�ȭ

	while (1) {
		printf("Ʈ������ ( 1:����  2:����  3:��� 4:���� ) \n�Է� : ");
		scanf("%d", &command);

		if (command == 1) {
			printf("add item : ");
			scanf("%d", &item);
			root = addtree(root, item);
		}
		else if (command == 2) {
			//�����Լ�
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

/*�����Լ� addtree����*/
struct tnode* addtree(struct tnode* p, int num) {	//���ڷ�(����������, �Է°�)�� �޾� Ʈ���� �����ϰ� ������p�� ����	
	if (p == NULL)				//p�� ����Ű�°� ������ ���� ex��Ʈ
	{
		p = (struct tnode*)malloc(sizeof(tnode));
		p->item = num;
		p->left = NULL;			//������NULL�ʱ�ȭ
		p->right = NULL;
	}
	else if (num == p->item)	//p�� ����Ű�°� ������
		printf("�����ϴ� �����Դϴ�. \n");
	else if (num < (p->item))	//���°��� ����parent���� ������
		p->left = addtree(p->left, num);	//���ʿ� �ּҰ� = ���(�����ּҰ�, �Է°�) 
	else if (num > (p->item))
		p->right = addtree(p->right, num);	//������ �ּҰ� = ���(�������ּҰ�, �Է°�) 

	return p;
}

/*����Ʈ�Լ� deletetree����*/

/*����Լ� treeprint����*/
void treeprint(struct tnode* p) {	//����Ž�� ���
	if (p != NULL) {
		treeprint(p->left);
		printf("%d\n", p->item);
		treeprint(p->right);
	}
}