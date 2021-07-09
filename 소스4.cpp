#include<stdio.h>
int main(void)		//scanf
{
	char a = '\0';
	char b = ' ';
	char c = 'A';


	char d = 'a';
	char e = 'a'; 
	int value = sizeof(char);
	scanf("%c", &d);


	printf("%d , %d , %d \n %d %d", a, b, c, d, value);

	return 0;
}