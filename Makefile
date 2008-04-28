CFLAGS= -g -O2 -m32
all: alg crypt decrypt encrypt bignum
.c:
	gcc $(CFLAGS) -o $@ $@.c
.cpp:
	g++ $(CFLAGS) -o $@ $@.cpp
clean:
	rm alg crypt decrypt encrypt
bignum: bignum.c bignum_asm bnmain.c
	gcc $(CFLAGS) bnmain.c bignum.c bignums.o -o bignum
bignum_asm: bignum.asm
	nasm -g -felf -o bignums.o bignum.asm
