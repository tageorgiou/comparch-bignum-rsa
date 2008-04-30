#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum.h"

#define SIZE 128
#define SIGNBIT ((SIZE<<3)-1)
#define BIT(IN,N) ((IN)[(SIZE-1)-(N>>3)]>>(N&7)&1)
#define SETBIT(IN,N,V) ((IN)[(SIZE-1)-(N>>3)]=(((IN)[(SIZE-1)-(N>>3)]|((V)<<(N&7))&(V)<<(N&7))))
#define COPY(A,B) (memcpy((A),(B),SIZE))

int leftmostbit(bignum a)
{
	int i;
	int lbit = -1;
	for (i = 0; i <= SIGNBIT; i++) {
		if (BIT(a,i)==1)
			lbit=i;
	}
	return lbit;
}

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

bignum bignum_from_string(char* string)
{
	bignum b = bignum_from_int(10);
	bignum d;
	bignum a = zero();
	int i;
	int negative = 0;
	for (i = 0; i < strlen(string); i++) {
		if (string[i] == '-') {
			negative=!negative;
			continue;
		}
		mul(a,b);
		d = bignum_from_int(string[i]-'0');
		add(a,d);
		free(d);
	}
	free(b);
	if (negative)
		neg(a);
	return a;
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

void sub(volatile bignum a, volatile bignum b)
{
	if (a==b) {
		memset(a,0,SIZE);
		return;
	}
	neg(b);
	add(a,b);
	neg(b);
}


static unsigned char shlbuf[SIZE];
int I = 0;
int B = 0;
void shl(bignum a, int b)
{
	COPY(shlbuf,a);
	memset(a,0,SIZE);
	int i;
	for (i = SIGNBIT; i >= b; i--) {
		I=i;
		B=b;
		SETBIT(a,i,BIT(shlbuf,i-b));
	}
	for (i = b-1; i >= 0; i--)
		SETBIT(a,i,0);
}

static unsigned char shrbuf[SIZE];
void shr(bignum a, int b)
{
	COPY(shrbuf,a);
	memset(a,0,SIZE);
	int i;
	for (i = b; i < SIZE<<3; i++) {
		SETBIT(a,i-b,BIT(shrbuf,i));
	}
	for (i = (SIZE<<3)-b; i < SIZE<<3; i++)
		SETBIT(a,i,0);
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

int cmp(bignum a, bignum b)
{
	int r=0,i;
	if (BIT(a,SIGNBIT) < BIT(b,SIGNBIT))
		return 1;
	if (BIT(a,SIGNBIT) > BIT(b,SIGNBIT))
		return -1;
	for (i=0; i < SIZE; i++) {
		if (a[i] < b[i]) {
			r=-1;
			break;
		}
		if (a[i] > b[i]) {
			r=1;
			break;
		}
	}
	if (BIT(a,SIGNBIT) == 1)
		r=-r;
	return r;
}

int ucmp(bignum a, bignum b)
{
	int r=0,i;
	for (i=0; i < SIZE; i++) {
		if (a[i] < b[i]) {
			r=-1;
			break;
		}
		if (a[i] > b[i]) {
			r=1;
			break;
		}
	}
	return r;
}

void mul(bignum a, bignum b)
{
	int sign;
	volatile bignum c = copy(a);
	sign=BIT(c,SIGNBIT);
	if (sign)
		neg(c);
	memset(a,0,SIZE);
	volatile bignum b2 = copy(b);
	if (BIT(b2,SIGNBIT)) {
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

void idiv(volatile bignum a, bignum b)
{
	int sign = BIT(a,SIGNBIT);
	if (sign)
		neg(a);
	volatile int c = 0;
	volatile bignum q = zero();
	volatile bignum b2 = copy(b);
	if (BIT(b2,SIGNBIT)) {
		sign=!sign;
		neg(b2);
	}
	while (ucmp(b2,a) < 0) {
		shl(b2,1);
		c++;
	}
	while (c >= 0) {
		if (cmp(b2,a) > 0) {
			SETBIT(q,c,0);
		}
		else {
			SETBIT(q,c,1);
			sub(a,b2);
		}
		shr(b2,1);
		c--;
	}
	//NOTE: a is remainder before this line
	if (sign)
		neg(q);
	memcpy(a,q,SIZE);
	free(q);
	free(b2);
}

void mod(volatile bignum a, bignum b)
{
	int sign = BIT(a,SIGNBIT);
	if (sign)
		neg(a);
	volatile int c = 0;
	volatile bignum b2 = copy(b);
	if (BIT(b2,SIGNBIT)) {
		sign=!sign;
		neg(b2);
	}
	while (ucmp(b2,a) < 0) {
		shl(b2,1);
		c++;
	}
	while (c >= 0) {
		if (cmp(b2,a) <= 0) {
			sub(a,b2);
		}
		shr(b2,1);
		c--;
	}
	//NOTE: a is remainder before this line
 	if (sign)
 		neg(a);
// 	memcpy(a,q,SIZE);
	free(b2);
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

long long long_from_bignum(bignum a)
{
	long long ret = 0;
	int i;
	for (i = 0; i < 8; i++) {
		ret |= a[SIZE-i-1]<<(i<<3);
	}
	return ret;
}

void _printnum(volatile bignum a, bignum base)
{
	if (is_zero(a))
		return;
	volatile bignum modded = copy(a);
	mod(modded,base);
	volatile char printval=long_from_bignum(modded) + '0';
	free(modded);
	idiv(a,base);
	_printnum(a,base);
	printf("%c",printval);
}

void printnum(bignum a)
{
	volatile bignum a2 = copy(a);
	if (BIT(a2,SIGNBIT)==1) {
		printf("-");
		neg(a2);
	}
	bignum base = bignum_from_int(10);
	_printnum(a2,base);
	printf("\n");
	free(a2);
}
