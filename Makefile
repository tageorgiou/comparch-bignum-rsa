CFLAGS= -g -O2 -m32
all: alg crypt decrypt encrypt bignum
.c:
	gcc $(CFLAGS) -o $@ $@.c
.cpp:
	g++ $(CFLAGS) -o $@ $@.cpp
clean:
	rm alg crypt decrypt encrypt
bignumc: bignum.c
	gcc $(CFLAGS) -O0 bignum.c -c
bignum: bignumc bignum_asm bnmain.c
	gcc $(CFLAGS) -O0 bnmain.c bignum.o bignums.o -o bignum
bignum_asm: bignum.asm
	nasm -g -felf -o bignums.o bignum.asm
encrypt: encrypt.c bignum
	gcc $(CFLAGS) -O0 -o encrypt encrypt.c bignum.o bignums.o -o encrypt
