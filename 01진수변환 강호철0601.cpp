/*16진수>10진수로 단순변수로 12P참고 v=c-'0'  12B가 입력되었다고 가정하고. */

#include<stdio.h>
#include<stdlib.h> //exit(0) == return 0 정상적종료 //exit(1) 비정상종료

int main(void)
{
	int c, value = 0, ndigit_16bit =0;

	/*printf("입력된값 : ");*/ //while문이 아래에있어서 값입력전에 나옴

	while ((c = getchar()) != '\n') 
	{
		if (c >= 0 && c <= '9') //1~9

			ndigit_16bit = c - '0';


		else if (c >= 'A' && c <= 'F') //10~14

			ndigit_16bit = c - 'A' + 10;	// 이게 중요! c에 B가들어오면 48만큼 제외하고 +10을하면 A가10 B가11 C가12 D가13 F가14가 됨.

		else {
			printf("16진수가 아닙니다\n");
			exit(1);

		}
		printf("%c", c); // getchar에서 나올때마다 12B 하나씩뱉어냄. 반복문이기때문에 입력된값: 입력시 프린트문 중복실행이 될수있음.

		value = (value * 16) + ndigit_16bit;  // value가 한번진행될수록 앞자리였던 value는 x16배 +나머지 ndigit
		
	}

	printf("\n 입력된값 %c 변환된값 %d \n", c, value); //입력된값은 다빠져나와안나옴

	return 0;
}



//원리
// '1' '2' 'B' 를 바꿔줌 (0*16)+1 가 (1*16)+2가되게 ((1*16)+2)*16+11  자리가더커질때마다16

//(0*16) +1
//    1       *16 + 2
//    ( (1*16) +2  )   *16 + 11