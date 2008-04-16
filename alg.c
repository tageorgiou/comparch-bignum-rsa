#include <stdio.h>
typedef unsigned int uint;
typedef struct {
	int x;
	int y;
} eea_t;
int kapow(int b, uint p, int mod)
{
	int ans = 1;
	while (p) {
		if (p&1)
			ans=(ans*b)%mod;
		p>>=1;
		b=(b*b)%mod;
	}
	return ans;
}
eea_t eea(int x, int y) {
	if (x%y == 0) {
		eea_t ret = {0,1};
		return ret;
	}
	else {
		eea_t tmp = eea(y,x%y);
		int a = tmp.x;
		tmp.x = tmp.y;
		tmp.y = a-tmp.y*(x/y);
		return tmp;
	}
}
int main(int argc, char* argv[])
{
	printf("%d %d\n",eea(17,3120));
}
