CC = gcc

interface: *.c
	$(CC) `pkg-config --cflags gtk+-3.0` -o example-0 InterfaceWithGTK.c `pkg-config --libs gtk+-3.0`  # note this command does not compile statically
	

