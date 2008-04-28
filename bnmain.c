#include <stdio.h>
#include "bignum.h"
int main(int argc, char* argv[])
{
	volatile bignum s = bignum_from_int(12342);
	printnum(s);
}

