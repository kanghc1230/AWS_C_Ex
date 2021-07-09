#include<stdio.h>
#include<stdlib.h> //exit
//����Ž��Ʈ�� ������ ������ �������� ū���� ������ ��ġ�ϴ� ����Ʈ��
struct tnode {
	int item;
	struct tnode* left;
	struct tnode* right;
};

struct tnode* addtree(struct tnode*,int);	//addtree�Լ� ����
void deletetree(struct tnode**, int);		//deletetree�Լ� ����
void treeprint(struct tnode*);				//treeprint�Լ� ����

int main(void)
{
	struct tnode* root;	
	int command;	//��� ���� ����
	int item;		//����,���� �� ���� ����
	root = NULL;	//��Ʈ���������� ù�� �۵��ǵ��� NULL�� �ʱ�ȭ

	while (1) {
		printf("\n����Ʈ������ ( 1:����  2:����  3:��� 4:���� ) \n�Է� : ");
		scanf("%d", &command);
		
		if (command == 1) {		
			printf("�߰��� item : ");
			scanf("%d", &item);
			root = addtree(root, item);
		}
		else if (command == 2) {
			printf("������ item : ");
			scanf("%d", &item);
			deletetree(&root, item);	//����������,�����Ұ�
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
		printf(" ERROR : �̹� �����ϴ� �����Դϴ�. \n\n");
	else if (num < (p->item))	//���°��� ����parent���� ������
		p->left = addtree(p->left, num);	//���ʿ� �ּҰ� = ���(�����ּҰ�, �Է°�) 
	else if (num > (p->item))
		p->right = addtree(p->right, num);	//������ �ּҰ� = ���(�������ּҰ�, �Է°�) 

	return p;
}

/*����Ʈ�Լ� deletetree����*/
void deletetree(struct tnode** root, int num) {		//����(��Ʈ���� ����������, �����Ұ�)
	struct tnode *deleted, *prev, *parent, *move;	//prev�� delete�Ǻθ�. parent�� move�� �θ�. move�̵��Ҵ��. 
	deleted = prev = parent = move = NULL;		//�ʱ�ȭ

	//num�� �ٰŷ� ������ deleted ��ġ ����
	deleted = *root;
	while (deleted) {				//1�̸� 
		if (num == deleted->item)
			break;
		else if (num < deleted->item) {		//num���� ������ delete �����̵�
			prev = deleted;
			deleted = deleted->left;
		}
		else { //(num > deleted->item)		//num���� ũ�� delete �������̵�
			prev = deleted;
			deleted = deleted->right;
		}
	}
	/* ���̾����� ���ư��� */
	if (deleted == NULL) {	//�����Ұ��� �������� ������
		printf(" ERROR : �������� �ʴ� ������ ������ �� �����ϴ�.\n\n");
		return;	//�ǵ��ư���
	}

	/* ���� ������ ���� */
	if (deleted->left) {		//���ʼ��� Ʈ������ ���� �ϴ� ���
		parent = deleted;		//parent�ʱⰪ
		move = deleted->left;	//move ����Ʈ���� �ʱⰪ
		//������ġ����
		while (move->right != NULL)	//move�� ������. �� ���� ū���� ã�ƿ�����.
		{
			parent = move;
			move = move->right;
		}

		//2�����̽� �밢������. parent==delete, �������ִ��� move���� ���ʳ�尡 �־������
		if (parent == deleted)	
			parent->left = move->left;
		//1�����̽� : �������ִ��� move���� ���ʳ�尡 �־������ ( ���� �� ���̾ �η� �̾��� ������� )
		parent->right = move->left;

		deleted->item = move->item;
		free(move);
	}

	else  if (deleted->right) {	// ������ ���� Ʈ������ ����
		parent = deleted;		//parent�ʱⰪ
		move = deleted->right;	//move ����Ʈ������ �ʱⰪ
		//������ġ����
		while (move->left != NULL) //move�� ����. �� ���� �������� ã�ƿ�����.
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


	//3�����̽� : �ܸ������ ������ NULL�����ֱ� (�� delete ��������� �ڽ��� ������)
	else  if (prev == NULL) {  // ���������� �ϳ� ���� ��� ���� �� ��� 
		free(deleted);
		*root = NULL;    // ���� Ʈ���� �Ǿ����� �˷� �ִ� �κ� 
	}
	else if (deleted == prev->left) {  // ���� �ܸ� ��� ������ ���
		prev->left = NULL;
		free(deleted);
	}
	else  if (deleted == prev->right) { // ������ �ܸ� ��� ������ ���
		prev->right = NULL;
		free(deleted);
	}
}

/*����Լ� treeprint����*/
void treeprint(struct tnode* p) {	//����Ž�� ���
	if (p != NULL) {
		treeprint(p->left);
		printf(" %d ", p->item);
		treeprint(p->right);
	}
}
