#include <stdio.h>
#include "bignum.h"

int main(int argc, char* argv[])
{
	bignum s;
	if (argc < 2)
		s = bignum_from_int(25);
	else
		s = bignum_from_string(argv[1]);
	printnum(s);
}
