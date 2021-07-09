#include<stdio.h>
int main(void)
{
	int num=0;
	unsigned int check = 0x80000000;			//unsigned int check 중요함 테스트
	
	scanf_s("%d", &num);		//scanf("%d", &num);

	for (int i = 0; i < 32; i++)
	{
		//for문으로 i%4==0마다 4칸마다' '넣기

		if((num&check)==0){
			printf("0");
			check = check >> 1;
			}
		else {
			printf("1");
			check = check >> 1;
		}

		//위에 중복되는 check문은 밖으로 빠질수있음 check = check >> 1;
	}

	// printf("\n"); 초기화가 일반적임

	return 0;
}


