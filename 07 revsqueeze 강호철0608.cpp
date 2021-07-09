//실습) 
//1. 주어진 문자열에서 또 다른 주어진 문자를 제거하고 압축한 후에, 
//2. 역순화 시킨 문자열을 만들어 주는 함수 revsqueeze(s, c) 를 만드시오.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *resqueeze(char*, char*);
int main()
{
	char s[20];	//주어진 문자열 받을s
	int i = 0;	//임시변수
	char c;		//제거할 문자열 받을c
	char* result;	//resqueeze 결과값(주소)를 받을 result포인터

	while ((s[i++] = getchar()) != '\n') //주어진 문자열받기
		;	//true
	s[i--] = '\0';

	c = getchar();	//제거할 문자열받기

	result = resqueeze(s, &c);		//s와 c 주소로 전달 
	
	printf("%s", result);	//result는 함수결과의 주소값받아서 출력

	return 0;
}

char* resqueeze(char* ps, char* pc)	//포인터로받음
{
	int i = 0;
	int j = 0;
	int len = strlen(ps);

	ps = ps + len - 1; // ps의 주소값에 +길이, 널-1칸. 주소ps는이제 s문자열의 끝의 주소를 가르킴.
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	char *temp = (char*)malloc(len + 1);	//포인터temp에, len+1크기만큼 생성하고 메모리주소 가르킴.
							  //만약 여기에 len이아니라 strlen(ps)를 사용했으면 바로위에 ps위치가 바뀌어서 len=1이됬을거야.
							  //결과는잘나와도 malloc범위 넘어서서 값입력되면 범위밖 나중에 덮어써질수있어 
	for (i = 1; i<len; i++)
	{
		ps--;
		if (*(ps) == *pc)			//ps-i가 가르키는곳 값이 == pc 가르키는곳 값이 같으면 넘기기
			;
		else{
			*(temp + j) = *(ps);
			j++;
		}
	}
	*(temp + j) = '\0';		//temp포인터가 가르키는 malloc마지막 len-1위치에, 값 = null
	
	return temp;	//return char* resqueeze 
}