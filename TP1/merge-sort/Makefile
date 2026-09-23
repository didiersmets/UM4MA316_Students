CC=gcc
CFLAGS=-g3 -Wall

all: main

main: main.o merge-sort.o print-array.o	 
	$(CC) $(CFLAGS) -o $@ $^
	echo "Build complete"

main.o: main.c
merge-sort.o: merge-sort.c merge-sort.h
print-array.o: print-array.c print-array.h

run: main
	./main

clean:
	$(RM) main *.o

