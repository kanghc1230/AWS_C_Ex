#include<stdio.h>
//더블포인터의 인자전달 int main(xxxx,xxxx) 설명하기위해

//포인터형 함수가 포인터를 받아옴


void showallstring(int argc, char *argv[])	//*argv[]
{
	int i;
	for (i = 0; i < argc; i++)
		printf("%s \n", argv[i]);	//argv[i]에는 char**형 주소값이 전달된다.
}

int main(void)
{
	char* str[3] = {
		"c progaming",
		"c++ progaming",
		"python progaming"
	};

	showallstring(3, str);

	
	return 0;

}