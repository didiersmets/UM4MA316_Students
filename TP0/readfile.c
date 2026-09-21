#include <stdio.h>


int main(int argc, char *argv[]) {


if (argc < 2) { 
return 1;
 }

FILE *file = fopen(argv[1], "r");

if (file  ==NULL) {
return 1;
}

char buffer[256];

while (fgets(buffer, sizeof(buffer), file) != NULL) {
printf("%s", buffer);
}

 
fclose(file);

return 0;

}
