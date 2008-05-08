#include <string.h>
#define SIZE 128
#define COPY(A,B) (memcpy((A),(B),SIZE))

typedef unsigned char* bignum;
void printbin(bignum a);
void add(bignum a,bignum b);
void not(bignum a);
void neg(bignum a);
void inc(bignum a);
void sub(bignum a,bignum b);
void shl(bignum a, int b);
void shr(bignum a, int b);
void printbin(bignum a);
void mul(bignum a, bignum b);
void mod(bignum a, bignum b);
void idiv(bignum a, bignum b);
void kapow(bignum a, bignum b, bignum m);
int cmp(bignum a, bignum b);
int ucmp(bignum a, bignum b);
int is_zero(bignum a);
int leftmostbit(bignum a);
bignum zero();
bignum copy(bignum a);
bignum bignum_from_int(long long a);
bignum bignum_from_string(char* string);
long long long_from_bignum(bignum a);
void printnum(bignum a);

