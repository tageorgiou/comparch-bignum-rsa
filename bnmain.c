#include <stdio.h>
#include "bignum.h"
int main(int argc, char* argv[])
{
	bignum s = bignum_from_string(argv[1]);
	bignum s2 = bignum_from_string(argv[2]);
	bignum m = bignum_from_int(10000);
	kapow(s,s2,m);
	printf("num:");
	printnum(s);
	free(s);
	free(s2);
	free(m);
}

