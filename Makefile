CFLAGS= -g -O2
all: alg crypt
.c:
	gcc $(CFLAGS) -o $@ $@.c
.cpp:
	g++ $(CFLAGS) -o $@ $@.cpp
