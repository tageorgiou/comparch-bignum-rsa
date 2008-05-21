#include <stdio.h>
#include "bignum.h"

long long longkapow(long long b, unsigned long long p, long long mod)
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

int main(int argc, char* argv[])
{
	long long basel = 2664;
	bignum baseb = bignum_from_int(basel);
	long long expl = 12553;
	bignum expb = bignum_from_int(expl);
	long long expl2 = 2141961817;
	bignum expb2 = bignum_from_int(expl2);
	long long modl = 2637478693;
	bignum modb = bignum_from_int(modl);
	
	basel = longkapow(basel, expl, modl);
	kapow(baseb,expb,modb);
	printf("%lld\n",basel);
	printnum(baseb);

	basel = longkapow(basel, expl2, modl);
	kapow(baseb,expb2,modb);
	printf("%lld\n",basel);
	printnum(baseb);
	int out = basel;
	fwrite(&out,1,4,stdout);
}
