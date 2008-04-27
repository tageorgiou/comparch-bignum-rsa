#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 8
#define BIT(IN,N) ((IN)[(SIZE-1)-(N>>3)]>>(N&7)&1)
#define SETBIT(IN,N,V) ((IN)[(SIZE-1)-(N>>3)]=(((IN)[(SIZE-1)-(N>>3)]|((V)<<(N&7))&(V)<<(N&7))))
typedef unsigned char* bignum;
extern void add(bignum a,bignum b);
void not(bignum a);
void neg(bignum a);
void inc(bignum a);
void sub(bignum a,bignum b);
void shl(bignum a, int b);
void shr(bignum a, int b);
void printbin(bignum a);
void mul(bignum a, bignum b);
bignum zero();
bignum copy(bignum a);
bignum bignum_from_int(long long a);

bignum bignum_from_int(long long a)
{
	char sign = 0;
	if (a<0) {
		sign = 1;
		a*=-1;
	}
	bignum num = zero();
	int n;
	for (n = 0; n < 8; n++)
		num[SIZE-n-1] = a>>(n<<3)&255;
	if (sign)
		neg(num);
	return num;
}

bignum copy(bignum a)
{
	bignum b = (bignum)malloc(SIZE);
	memcpy(b,a,SIZE);
	return b;
}

bignum zero() 
{
	bignum a = (bignum)malloc(SIZE);
	memset(a,0,SIZE);
	return a;
}

void neg(bignum a) {
	not(a);
	inc(a);
}

void sub(bignum a,bignum b)
{
	if (a==b) {
		memset(a,0,SIZE);
		return;
	}
	neg(b);
	add(a,b);
	neg(b);
}

void shl(bignum a, int b)
{
	bignum c = copy(a);
	memset(a,0,SIZE);
	int i;
	for (i = SIZE<<3-1; i >= b; i--)
		SETBIT(a,i,BIT(c,i-b));
	for (i = b-1; i >= 0; i--)
		SETBIT(a,i,0);
	free(c);
}

void shr(bignum a, int b)
{
	bignum c = copy(a);
	memset(a,0,SIZE);
	int i;
	for (i = b; i < SIZE<<3; i++) {
		SETBIT(a,i-b,BIT(c,i));
	}
	for (i = SIZE<<3-b; i < SIZE<<3; i++)
		SETBIT(a,i,0);
	free(c);
}

int is_zero(bignum a)
{
	int n;
	int z = 1;
	for (n=0; n < SIZE; n++) {
		z=z&&!a[n];
	}
	return z;
}

void mul(bignum a, bignum b)
{
	int sign;
	volatile bignum c = copy(a);
	sign=BIT(c,SIZE<<3-1);
	if (sign)
		neg(c);
	memset(a,0,SIZE);
	volatile bignum b2 = copy(b);
	if (BIT(b2,SIZE<<3-1)) {
		sign=!sign;
		neg(b2);
	}
	while (!is_zero(b2)) {
		if (BIT(b2,0)==1)
			add(a,c);
		shr(b2,1);
		shl(c,1);
	}
	if (sign)
		neg(a);
	free(c);
	free(b2);
}

void idiv(bignum a, bignum b)
{

}

void printbin(bignum num)
{
	int i;
	for (i = 0; i < SIZE; i++) {
		int a;
		for (a = 7; a >= 0; a--) {
			printf("%d",(num[i]>>a)&1);
		}
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	bignum five = bignum_from_int(23);
	printbin(five);
	bignum four = bignum_from_int(43);
	printbin(four);
	mul(five,four);
	printbin(five);

	free(four);
	free(five);
}
