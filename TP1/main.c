#include <stdio.h>
#include <time.h>


int main(){

	int val[] = {10, 20, 50, 100,200,500,1000};
	int taille_val = sizeof(val)/sizeof(val[0]);

	int t_bubble[taille_val];
        int t_insert[taille_val];
	int t_merge[taille_val];	

	for(int i = 0,i <  taille_val,i++){
		int *p = malloc(sizeof(int)*val[i]);
		for(int j = 0,j< val[i],j++){
			p[j] = rand();
		}
		p' = copy(p);
		bubble_sort(p',val[i]);
		t_insert[i] = time;

		free(*p);
		free(p);

	}

	return 0;
}
