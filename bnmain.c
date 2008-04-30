#include <stdio.h>
#include "bignum.h"
int main(int argc, char* argv[])
{
	bignum s = bignum_from_string(argv[1]);
	printbin(s);
	printnum(s);
}

