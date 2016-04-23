# MAKEFILE

CC = gcc

all: randcpuid.o, randlibhw.so, randlibsw.so, randmain

randcpuid.o:		randcpuid.c
	$(CC) -c randcpuid.c

randlibhw.so:		randlibhw.c
	$(CC) randlibhw.c -shared -fPIC -o randlibhw.so

randlibsw.so:		randlibsw.c
	$(CC) randlibsw.c -shared -fPIC -o randlibsw.so

randmain:		randcpuid.o
	$(CC) randmain.c randcpuid.o -ldl -Wl,-rpath=. -o randmain






