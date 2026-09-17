#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  
  int N = atoi(argv[1]);
  int *a_old = malloc(N * sizeof(int));
  int *a_new = malloc(N * sizeof(int));

  for (int i=0; i<N; i++) {

    for (int j=0; j<i; j++) {

      if (0 < j && j < i) {
        a_new[j] = a_old[j-1] + a_old[j];
      }
      else {
        a_new[j] = 1;
      }
      
      printf("%d  ", a_new[j]);
    }
    
    printf("\n");
    int *tmp = a_old;
    a_old = a_new;
    a_new = tmp;
  }
  free(a_old);
  free(a_new);
  return 0;
}
