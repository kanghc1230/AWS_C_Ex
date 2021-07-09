#include<stdio.h>
#include<string.h>
//사전에 먼저 나오는지 

int mystrcmp(char[], char[]);				//문자열 2개 비교함수 배열2개 인자로받아오기위해
											//인자 이름은 아래에서 정의할때씀
int main(void) 
{
	char s[20];		//첫번째 받을 문자열
	char t[20];		//두번째 받을 문자열
	int i = 0;		//임시변수i
	int j = 0;		//임시변수j
	int value = 0;	//결과값출력용변수

	while ((s[i] = getchar()) != '\n')		//s[i]에 차례대로 getchar(), \n엔터칠때까지
		i++;
	s[i] = '\0';	//\n대신 널\0넣기		
	//위에가 while ((s[i++] = getchar()) != '\n');였으면 줄끝날때 i가 자동적으로 ++되기에 s[--i] = \0;로
											
	while ((t[j] = getchar()) != '\n')	
		j++;
	t[j] = '\0';

	value = mystrcmp(s, t);		// mystrcmp == s>t면 1, t<s면 -1, t=0이면 0값 리턴하는 함수
								// 인자 s, t 주소값 전달. 물론 배열이니까 걍 s,t
	printf("%d", value);

	return 0;
}

int mystrcmp(char ps[], char pt[])	//배열은 이렇게 걍 ps[]로 받음 
{
	int a = strlen(ps);	
	int b = strlen(pt);
	int len;

	if (a >= b)		//길이가 긴쪽이 len
		len = a;	
	else
		len = b;

	//	for (int i = 0; pt[i] != '\0' || ps[i] != '\0' ; i++)시 길이비교 할필요x. 연산자순서 != || |
	for (int i = 0; i < len; i++)	//길이긴것까지 비교
	{
		if (ps[i] > pt[i])		//ps[i]가 크면 1리턴
			return 1;
		else if (ps[i] < pt[i])	//pt[i]가 크면 -1리턴
			return -1;
		else					//ps,pt[i]가 같으면 걍true 다시 for문으로
			;
	}
	return 0;	//둘다같으면 0리턴
}
