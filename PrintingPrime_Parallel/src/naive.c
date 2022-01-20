#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


bool isprime(int n){
    if( n== 1){
        return true;
    }
    for(int i=2; i<= sqrt(n); i++){
        if(n%i == 0){
            return false;
        }
    }
    return true;
}

struct naive_thread_data{
   int* domain;
   int* arr;
   double* time;
   int threadid;
};

void* naive_approach( void* a ){

    clock_t startt, endt;
    double cpu_time_used;
    startt = clock();

    struct naive_thread_data*  var = (struct naive_thread_data*) a;
    int *domain = var->domain;
    int start = domain[0];
    int end = domain[1];
    int* num = var->arr;
    int threadid = var->threadid;
    double* timeArray = var->time;
    for(int i=start; i<=end ; i++){
        if(isprime(i)){
            //printf("%d ",i);
            num[i-1] = 1;
        }
    }

    endt = clock();
    cpu_time_used = ((double) (endt - startt)) / CLOCKS_PER_SEC;
    timeArray[threadid] = cpu_time_used;
    //printf("%lf \n",cpu_time_used);
    return NULL;
}

int main(int argc, char* argv[]){
    FILE *fptr;
    fptr = fopen("./output/naive_prime.txt","w");

    // int numthreads = atoi(argv[1]);
    // char* strategy = argv[2];
    // int N = atoi(argv[3]);
    int N = atoi(argv[1]);
    int numthreads = atoi(argv[2]);

    pthread_t* threads;
    threads = (pthread_t*) malloc(numthreads*sizeof(pthread_t));

    //NAIVE APPROACH
    //if(strcmp(strategy, "naive") == 0){
        int total_num = N-1;
        int partition_size = total_num/numthreads;

        //Stores the time taken by the threads
        double* time_array;
        time_array = (double*)malloc(numthreads * sizeof(double*));

        //array which stores whether an integer is prime or not
        int *num;
        num = (int*)malloc(N * sizeof(int*));
        for(int i=0; i<N ; i++){
            num[i] = 0;
        }

        int r = numthreads;
        int c = 2;
        int **domain;
        domain = (int**)malloc(r * sizeof(int*));
        for (int i=0; i<r; i++)
             domain[i] = (int *)malloc(c * sizeof(int));

        int start = 2;
        int end = 2 + partition_size -1;
        for(int i=0; i<r-1 ; i++){
            domain[i][0] = start;
            domain[i][1] = end;
            start += partition_size;
            end += partition_size;
        }
        domain[r-1][0] = start;
        domain[r-1][1] =  N;

        struct naive_thread_data* thr;
        thr = (struct naive_thread_data*)malloc(numthreads*sizeof(struct naive_thread_data));
        for(int k=0; k<numthreads ; k++){
            thr[k].domain = domain[k];
            thr[k].arr = num;
            thr[k].threadid = k;
            thr[k].time = time_array;
        }

        for(int i=0; i<numthreads ; i++){
            pthread_create(&threads[i], NULL, naive_approach, (void* )&thr[i]);
        }

        for(int j=0; j<numthreads; j++){
            pthread_join(threads[j],NULL);
        }
        //printf("\n\n");
        for(int i=0; i<N; i++){
            if(num[i] == 1){
                //printf("%d ",i+1);
                fprintf(fptr, "%d ",i+1);
            }
        }
        fprintf(fptr, "\n");
    
        FILE *fptr1;
        fptr1 = fopen("./output/naive_threadTime.txt","w");
        for(int i=0; i<numthreads; i++){
           //fprintf(fptr1, "Thread %d took %lf seconds\n.",i+1,time_array[i]);
            fprintf(fptr1, "%d %lf\n",i+1,time_array[i]);
        }
        //fprintf(fptr1, "\n");

    return 0;
}
