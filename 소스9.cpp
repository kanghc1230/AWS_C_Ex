#include <stdio.h>	
//�����Լ��� ��������

//������ cmd�� debug�ȿ��ִ� exe���� ����

int main(int argc, char* argv[])
{
	int i = 0;
	printf("���޵� �ܾ��Ǽ� %d \n" , argc);

	for (i = 0; i < argc;)
		printf("%d��° ���ڿ� %s \n", i + 1, argv[i]);
	return 0;
}

//c:\>argvargv i like you �Է½�

//main(4,strArr);ȣ��???