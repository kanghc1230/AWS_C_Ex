#include <stdio.h>

int main(void)
{
	char str[7];
	char* str2[3];
	int i;

	for (i = 0; i < 3; i++)
	{
		fgets(str, sizeof(str), stdin);			//23456789098765432 6+\0ĭ�� �Ѱ踦 �Ѵ°��� �Է��ص�
		str2[i] = str;							//���Ҵ��� str2[0]->"123456" str[1]->"789098 ......

		printf("read : %d : %s \n", i + 1, str);	//�������

		printf("point str2 %s \n" , str2[i]);
	}
	return 0;
}