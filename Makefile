CFLAGS= -g -O2
all: alg
.c:
	gcc $(CFLAGS) -o $@ $@.c
.cpp:
	g++ $(CFLAGS) -o $@ $@.cpp
