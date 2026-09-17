#include <stdio.h>

int main(){

  FILE *r_file = fopen("../test-tp0.txt", "r");
  
  // pour voir que ça ne marche pas quand je lance l'executable du même niveau que le .txt
  if (r_file == NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    return 1;
  }

  char line[256];

  while(fgets(line, sizeof(line), r_file) != NULL) {
    printf("%s", line);
  }

  fclose(r_file);
  return 0;
}
