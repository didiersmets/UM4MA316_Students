#include <stdio.h> 
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>
void bubble_sort(int *T, int n);
void insertion_sort(int *T, int n);
void merge_sort(int *T, int n);
void timer_start(struct timeval *tv){
    gettimeofday(tv,NULL);
}
unsigned inttimer_stop(const struct timeval *tv,const char *str){
    struct timeval now;
    gettimeofday(&now,NULL);
    unsigned int mus=1000000 * (now.tv_sec-tv->tv_sec);
    mus+=(now.tv_usec-tv->tv_usec);
    if(str[0]){
        printf("Timer%s:",str);
        if(mus>=1000000){
            printf("%.3fs\n",(float)mus/1000000);
        }
        else{
            printf("%.3fms\n",(float)mus/1000);
        }
    }
    return(mus);
}

int main() {
    int Ns[] = {10, 20, 50,75 ,100, 150,200,300,350 ,400,500, 1000,2000,3000,3500,5000,7000,10000};
    int count = sizeof(Ns) / sizeof(Ns[0]);
    FILE *fp = fopen("sort_times.csv", "w");
    if (!fp) return 1;
    for (int k = 0; k < count; ++k) {
        int N = Ns[k];
        int *arr = malloc(N * sizeof(int));
        for (int i = 0; i < N; ++i) arr[i] = rand();
        struct timeval tv;
        timer_start(&tv);
        bubble_sort(arr, N);
        // insertion_sort(arr, N);
        merge_sort(arr, N);
        double t1 = inttimer_stop(&tv,"t");
        fprintf(fp, "%d %g\n", N, t1);
        free(arr);
    }
    fclose(fp);
    system("gnuplot -e \"set logscale xy; plot 'sort_times.dat' with linespoints\" -persist");
    return 0;
}