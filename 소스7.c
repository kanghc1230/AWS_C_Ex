#include <stdio.h>
//394p 함수 포인터와 const

void simpleadder(int n1, int n2)
{
	printf("%d + %d = %d \n", n1, n2, n1 + n2);
}

void showstring(char* str)
{
	printf("%s \n", str);
}

int main(void)
{
	const char* str = "function pointer";	//c++에서는 const char* str = "function pointer"; 방식 c에서는 char *str ="문자열";해도잘됨.
	
	int num1 = 10 , num2 = 20;

	void (*fptr1)(int, int) = simpleadder;	//함수 포인터 선언방법 = 함수명;
	void (*fptr2)(char *) = showstring;		//char * ?

	//함수 포인터 변수에 의한 대리호출

	fptr1(num1, num2);
	fptr2(str);			//위와 같은이유로 cpp에선 안됨 const 함수로 호출불가? 파일c로변경시됨


	return 0;
}