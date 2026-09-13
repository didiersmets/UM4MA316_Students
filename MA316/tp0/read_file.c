#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 256

int main(int argc, char **argv) {
  FILE *f;
  char line[MAX_LINE];

  if (argc != 2) {
    printf("Usage: %s <name of the file>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Error: Could not open file %s\n", argv[1]);
    return 1;
  }

  while (fgets(line, (sizeof(line)), f) != NULL) {
    printf("%s", line);
  }

  fclose(f);

  return 0;
}