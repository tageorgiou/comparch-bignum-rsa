CFLAGS= -g -O2
all: alg crypt decrypt encrypt bignum
.c:
	gcc $(CFLAGS) -o $@ $@.c
.cpp:
	g++ $(CFLAGS) -o $@ $@.cpp
clean:
	rm alg crypt decrypt encrypt
bignum: bignum.c bignum.asm
	nasm -g -felf -o bignums.o bignum.asm
	gcc $(CFLAGS) bignum.c bignums.o -o bignum
