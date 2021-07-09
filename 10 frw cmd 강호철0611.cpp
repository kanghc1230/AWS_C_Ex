#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[])
{
	int i=0;
	char c;
	FILE* fp;
	FILE* fpl;

	//getc //putc 활용할것
	// 
	/*frw 키보드입력 화면에뿌려주기*/
	if (argc == 1)
		while ((c = getc(stdin)) != EOF)
			putc(c, stdout);

	/*frw파일 test.txt읽어서 화면에뿌려주기*/
	else if (argc == 2) {	//frw test.txt
		fp = fopen(*(argv + 1), "r");	//argv2 파일1읽기
		while ((c = getc(fp)) != EOF)
			putc(c,stdout);				//stdout화면출력
		fclose(fp);
	}
	/*argc 2번에 @가 있으면 타이핑을 파일로,, @없으면 일반파일을 읽어오고 파일로 출력"w"*/
	else if (argc == 3)
		if ( !(strcmp(argv[1],"@")) )			//if(argv[1]==@)왜 안먹힌다. 주소가달라서??  if (!strcmp(argv[1]), "@")로 비교해라?
		{
			fp = fopen(*(argv + 2), "w+");		//fp에 argc3 파일1읽고쓰고
			while ((c = getc(stdin)) != EOF)	//== c = fgetc(stdin); fgetc는 문자끝이나 eof까지알아서
				putc(c, fp);					//c를 fp에 뿌려줘라
			fclose(fp);
		}
		else {
			fp = fopen(*(argv + 1), "r");		//fp에 파일1읽기용
			fpl = fopen(*(argv + 2), "w");		//fpl에 파일2쓰기용
			while ((c = getc(fp)) != EOF)		//c로받음	//== c = fgetc(fp);		
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
		// 위에꺼 안먹힌다. 주소가달라서?? 
		// if (!strcmp(argv[1]), "@")로 비교해라?

		//타이핑 sp = argv[1];