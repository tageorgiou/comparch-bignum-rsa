#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 8
typedef unsigned char* bignum;
void add(bignum a,bignum b);
bignum zero() 
{
	bignum a = (bignum)malloc(size);
	memset(a,0,size);
	return a;
}

void printbin(bignum num)
{
	int i;
	for (i = 0; i < size; i++) {
		int a;
		for (a = 7; a >= 0; a--) {
			printf("%d",(num[i]>>a)&1);
		}
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	bignum five = zero();
	five[7]=254;
	printbin(five);
	bignum four = zero();
	four[7]=2;
	printbin(four);
	add(five,four);
	printbin(five);
}
