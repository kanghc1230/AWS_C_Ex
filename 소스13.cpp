#include <stdio.h>

int main(void)
{
	char str[7];
	char* str2[3];
	int i;

	for (i = 0; i < 3; i++)
	{
		fgets(str, sizeof(str), stdin);			//23456789098765432 6+\0칸의 한계를 넘는값을 입력해도
		str2[i] = str;							//분할대입 str2[0]->"123456" str[1]->"789098 ......

		printf("read : %d : %s \n", i + 1, str);	//분할출력

		printf("point str2 %s \n" , str2[i]);
	}
	return 0;
}