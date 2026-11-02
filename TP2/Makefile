CC = cc
CFLAGS = -Wall -Wextra

test_area: main.c mesh2D.c readmesh.c mesh2D.h
	$(CC) $(CFLAGS) main.c mesh2D.c readmesh.c -o test_area

clean:
	rm -f test_area *.o
