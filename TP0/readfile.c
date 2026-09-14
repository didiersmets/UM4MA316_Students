#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Please enter correctly.");
		return 1;
	}
	FILE *f=fopen(argv[1], "r");
	char line[1000];
	while(fgets(line, sizeof(line), f)!=NULL){
		printf("%s", line);
	}
	fclose(f);
	return 0;
}
