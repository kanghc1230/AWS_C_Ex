#include<stdio.h>
int main(void){
	//float x, y;
	//x = 5.0e10 + 12.3;
	//y = x - 5.0e10;
	//printf("%f \n %f", x,y);
	//return 0;


	//int x = -1, y = -1, z = 1, k;
	//k = ++x && ++y || ++z;
	//printf("%d %d %d %d", k, x, y, z);
	//return 0;

	//int x = -123;
	//unsigned int y = -123;
	//printf("%x\n", x >> 3);
	//printf("%x\n", y >> 3);
	//return 0;

	int a[5] = { 0,1,2,3,4 };
	int* p = a;
	printf("%d", (int)(p + 1) - (int)(p));
	return 0;
}
