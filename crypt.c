#include <stdio.h>
typedef long long bignum;
typedef unsigned int uint;
typedef struct {
	bignum x;
	bignum y;
} eea_t;
void printbin(uint in)
{
	unsigned int mask;
	for (mask = 1<<31; mask; mask>>=1)
		putchar(!!(in&mask)+'0');
	putchar('\n');
}
bignum kapow(long long b, unsigned long long p, int mod)
{
	long long ans = 1;
	while (p) {
		if (p&1)
			ans=(ans*b)%mod;
		p>>=1;
		b=(b*b)%mod;
	}
	return ans;
}
eea_t eea(bignum x, bignum y) {
	if (x%y == 0) {
		eea_t ret = {0,1};
		return ret;
	}
	else {
		eea_t tmp = eea(y,x%y);
		bignum a = tmp.x;
		tmp.x = tmp.y;
		tmp.y = a-tmp.y*(x/y);
		return tmp;
	}
}
int main(int argc, char* argv[])
{
	bignum p = 5227, q = 5113;
	bignum n = p*q;
	bignum t = (p-1)*(q-1);
	bignum e = 65539;
	eea_t tmp = eea(e,t);
	printf("%lld %lld\n",eea(e,t));
	bignum d = tmp.x;
	//d=2753;
	printf("p:%lld q:%lld n:%lld t:%lld\n",p,q,n,t);
	printf("e:%lld d:%lld\n",e,d);
	int m = atoi(argv[1]);
	bignum c = kapow(m,e,n);
	int dec = kapow(c,d,n);
	printf("orig:%d enc:%lld dec:%d\n",m,c,dec);
}
