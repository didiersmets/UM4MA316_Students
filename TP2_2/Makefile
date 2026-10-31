CC=gcc
CFLAGS=-Wall -g3 -std=c99

all: main

main: main.o mesh.o
	$(CC) $(CFLAGS) -o $@ $^
	echo "Build complete!"

main.o: main.c

mesh.o: mesh.c mesh.h

clean:
	$(RM) *.o ./main
