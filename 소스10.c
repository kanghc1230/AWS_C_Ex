#include<stdio.h>
//������������ �������� int main(xxxx,xxxx) �����ϱ�����

//�������� �Լ��� �����͸� �޾ƿ�


void showallstring(int argc, char *argv[])	//*argv[]
{
	int i;
	for (i = 0; i < argc; i++)
		printf("%s \n", argv[i]);	//argv[i]���� char**�� �ּҰ��� ���޵ȴ�.
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