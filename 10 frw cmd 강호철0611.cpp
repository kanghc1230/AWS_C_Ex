#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
	int i=0;
	char c;
	FILE* fp;
	FILE* fpl;

	//getc //putc Ȱ���Ұ�
	// 
	/*frw Ű�����Է� ȭ�鿡�ѷ��ֱ�*/
	if (argc == 1)
		while ((c = getc(stdin)) != EOF)
			putc(c, stdout);

	/*frw���� test.txt�о ȭ�鿡�ѷ��ֱ�*/
	else if (argc == 2) {	//frw test.txt
		fp = fopen(*(argv + 1), "r");	//argv2 ����1�б�
		while ((c = getc(fp)) != EOF)
			putc(c,stdout);				//stdoutȭ�����
		fclose(fp);
	}
	/*argc 2���� @�� ������ Ÿ������ ���Ϸ�,, @������ �Ϲ������� �о���� ���Ϸ� ���"w"*/
	else if (argc == 3)
		if ( !(strcmp(argv[1],"@")) )			//if(argv[1]==@)�� �ȸ�����. �ּҰ��޶�??  if (!strcmp(argv[1]), "@")�� ���ض�?
		{
			fp = fopen(*(argv + 2), "w+");		//fp�� argc3 ����1�а���
			while ((c = getc(stdin)) != EOF)	//== c = fgetc(stdin); fgetc�� ���ڳ��̳� eof�����˾Ƽ�
				putc(c, fp);					//c�� fp�� �ѷ����
			fclose(fp);
		}
		else {
			fp = fopen(*(argv + 1), "r");		//fp�� ����1�б��
			fpl = fopen(*(argv + 2), "w");		//fpl�� ����2�����
			while ((c = getc(fp)) != EOF)		//c�ι���	//== c = fgetc(fp);		
				putc(c, fpl);					//fputc(c, fpl);
			fclose(fp);
			fclose(fpl);
		}

	else
	{
		printf("wrong input \n");
		exit(1);
	}

	printf("\n");
	return 0;
}	
		// ������ �ȸ�����. �ּҰ��޶�?? 
		// if (!strcmp(argv[1]), "@")�� ���ض�?

		//Ÿ���� sp = argv[1];