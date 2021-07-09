//문자열 2개받아와서 fcmp로 분류하고 적합함수 포인터연결 함수numcmp strcmp로. 비교값출력

#include<stdio.h>
#include<ctype.h>
#include<string.h>//strcmp
#include<stdlib.h> //atof
//strcmp 문자비교함수 a>b 1 a<b -1 같으면0
int numcmp(const char*, const char*); //숫자비교함수 a>b 1 a<b -1 같으면0 
void fcmp(int (**p)(const char*, const char*), char* ps, char* pt);	//문자숫자 판단해 문자함수,숫자함수연결
int main(void)
{
	char s[80];
	char t[80]; //값2개
	int (*ptr)(const char*, const char*);	//ptr은 포인터for함수

	scanf("%s %s", s, t);

	fcmp(&ptr, s, t); // 문자숫자구별 함수fcmp(함수포인터,배열,배열) 콜 //*ptr에 **p로 numcmp혹은 strcmp가 연결

	printf("%d \n", ptr(s, t));		//ptr에 연결된함수 콜(s,t) 프린트.
									//numcmp 혹은 strcmp
	return 0;
}

void fcmp(int (**p)(const char*, const char*), char* ps, char* pt)	//포인터ptr을 더블포인터로, s, t
{
	//ps확인
	if (*ps == '-')	//-제외
		ps++;
	while (*ps != '\0')
	{						//sdigit((*ps)-'0') isdigit은 캐릭터를 넣어야함.문자열!이 숫자면 true 1
		if (isdigit(*ps))	//*ps가 숫자면
			ps++;			//주소 ps+1
		else if(*ps == '.') //*ps가 '.'이면
			ps++;
		else				//ps가 문자면
		{
			*p = strcmp;	//더블포인터p에 문자비교함수 연결
			return;			//함수끝 (주의!) c에선되지만 특정언어서 void라고 return치면 에러날수있다.
		}
	}
	//pt확인
	if(*pt =='-')//-제외
		pt++;
	while (*pt != '\0') 
	{
		if (isdigit(*pt))	//*ps가 숫자면
			pt++;
		else if (*pt == '.')//*ps가 '.'이면
			pt++;
		else				//ps가 문자면
		{
			*p = strcmp;	//더블포인터p에 문자비교함수 연결
			return;			//함수끝
		}	
	}
	*p = numcmp;	//문자열이없다.더블포인터p에 숫자비교함수 연결
}

int numcmp(const char* ps, const char* pt)	//num비교함수
{
	float a, b;

	a = atof(ps);	//문자 a,b둘다 실수로바꾸기
	b = atof(pt);	

	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}