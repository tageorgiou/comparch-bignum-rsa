#include <stdio.h>
#include "bignum.h"
typedef struct {
	bignum x;
	bignum y;
} eea_t;
typedef struct {
	bignum n;
	bignum d;
} priv_key;
typedef struct {
	bignum n;
	bignum e;
} pub_key;

//static unsigned char eeabufa[SIZE];
eea_t eea(bignum a, bignum b) {
	bignum eeabufa = copy(a);
//	COPY(eeabufa,a);
	mod(eeabufa,b);
	if (is_zero(eeabufa)) {
		eea_t retval;
		retval.x = zero();
		retval.y = zero();
		inc(retval.y);
		free(eeabufa);
		return retval;
	} else {
		eea_t retval = eea(b,eeabufa);
		bignum tmp = retval.x;
		retval.x = retval.y;
		retval.y = copy(a);
		idiv(retval.y,b);
		mul(retval.y,retval.x);
		neg(retval.y);
		add(retval.y,tmp);
		free(tmp);
		free(eeabufa);
		return retval;
	}
}
/*eea_t eea(bignum x, bignum y) {
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
}*/
/*bignum encrypt(pub_key key, uint m)
{
	return kapow(key->c,m,key->n);
}
bignum decrypt(priv_key key, uint m)
{

}*/
int main(int argc, char* argv[])
{
	printf("size:%d\n",SIZE);
	bignum one = bignum_from_int(1);
	bignum p,q,n,t,e;
	p = bignum_from_int(54121);
	q = bignum_from_int(48733);
	n = copy(p);
	mul(n,q);
	t = copy(p);
	sub(t,one);
	mul(t,q);
	sub(t,p);
	inc(t);
	e = bignum_from_int(12553);
	printf("p:");
	printnum(p);
	printf("q:");
	printnum(q);
	printf("n:");
	printnum(n);
	printf("t:");
	printnum(t);
	printf("e:");
	printnum(e);
	eea_t tmp = eea(e,t);
	printnum(tmp.x);
	printnum(tmp.y);
	bignum d = tmp.x;
	bignum zeronum = zero();
	if (cmp(d,zeronum) < 0) {
		add(d,t);
	}
	printnum(d);
	printf("-------\n");
	FILE* fin = fopen(argv[1],"r");
	FILE* fout = fopen(argv[2],"w");
	while (!feof(fin)) {
		char m[4];
		int i;
		for (i = 0; i < 4; i++) {
			m[i] = fgetc(fin);
			if (feof(fin))
				m[i] = 0;
		}
		bignum out = bignum_from_int(*(unsigned int*)m);
		kapow(out,e,n);
		long long outnum = long_from_bignum(out);
		fwrite(&outnum,1,8,fout);
	}
/*	bignum p = 54121, q = 48733;
	bignum n = p*q;
	bignum t = (p-1)*(q-1);
	bignum e = 12553;
	eea_t tmp = eea(e,t);
//	printf("%lld %lld\n",eea(e,t));
	bignum d = tmp.x;
	if (d < 0) 
		d+=t;*/
	//d=2753;
/*	printf("p:%lld q:%lld n:%lld t:%lld\n",p,q,n,t);
	printf("e:%lld d:%lld\n",e,d);
	uint m = atoi(argv[1]);
	//int m;
	//m = *(int*)"hel";
	bignum c = kapow(m,e,n);
	uint dec = kapow(c,d,n);
	printf("orig:%d enc:%lld dec:%d\n",m,c,dec);
	//printf("orig:%s dec:%s\n",&m,&dec);
	*/
/*	FILE* fin = fopen(argv[1],"r");
	FILE* fout = fopen(argv[2],"w");
	while (!feof(fin)) {
		char m[4];
		int i;
		for (i = 0; i < 4; i++) {
			m[i] = fgetc(fin);
			if (feof(fin))
				m[i] = 0;
		}
		bignum out = kapow(*(unsigned int*)m,e,n);
//		fprintf(fout,"%c%c%c%c%c%c",out);
		fwrite(&out,1,8,fout);
	}*/
}
