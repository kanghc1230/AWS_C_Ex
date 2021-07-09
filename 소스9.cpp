#include <stdio.h>	
//메인함수의 인자전달

//실행방법 cmd로 debug안에있는 exe파일 실행

int main(int argc, char* argv[])
{
	int i = 0;
	printf("전달된 단어의수 %d \n" , argc);

	for (i = 0; i < argc;)
		printf("%d번째 문자열 %s \n", i + 1, argv[i]);
	return 0;
}

//c:\>argvargv i like you 입력시

//main(4,strArr);호출???