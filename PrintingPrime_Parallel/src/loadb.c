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

struct loadbalanced_thread_data{
   int* counter;
   int* arr;
   int n;
   double* time;
   int threadid;
};

void* loadbalanced_approach(void* a){

    clock_t startt, endt;
    double cpu_time_used;
    startt = clock();

    struct loadbalanced_thread_data*  var = (struct loadbalanced_thread_data*) a;
    int* num = var->arr;
    int* count = var->counter;
    int N = var->n;
    int threadid = var->threadid;
    double*  timeArray = var->time;
    while(1){
        pthread_mutex_lock(&mutex);
        if(*count >= N){
            pthread_mutex_unlock(&mutex);
            endt = clock();
            cpu_time_used = ((double) (endt - startt)) / CLOCKS_PER_SEC;
            timeArray[threadid] = cpu_time_used;
            //printf("%lf \n",cpu_time_used);
            return NULL;
        }
        else{
            if(isprime(*count+1)){
                num[*count] = 1;
                *count += 1;
                pthread_mutex_unlock(&mutex);
            }
            else{
                 *count += 1;
                 pthread_mutex_unlock(&mutex);
            }
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
    fptr = fopen("./output/load_balanced_prime.txt","w");

    // int numthreads = atoi(argv[1]);
    // char* strategy = argv[2];
    // int N = atoi(argv[3]);
    int N = atoi(argv[1]);
    int numthreads = atoi(argv[2]);

    pthread_t* threads;
    threads = (pthread_t*) malloc(numthreads*sizeof(pthread_t));
    
    //LOAD BALANCED APPROACH

        //Stores the time taken by the threads
        double* time_array;
        time_array = (double*)malloc(numthreads * sizeof(double*));

        int *num;
        num = (int*)malloc(N * sizeof(int*));
        for(int i=0; i<N ; i++){
            num[i] = 0;
        }
        int coun = 1;
        int* counter = &coun;

        struct loadbalanced_thread_data* thr;
        thr = (struct loadbalanced_thread_data*)malloc(numthreads*sizeof(struct loadbalanced_thread_data));
        for(int k=0; k<numthreads ; k++){
            thr[k].counter = counter;
            thr[k].arr = num;
            thr[k].n = N;
            thr[k].threadid = k;
            thr[k].time = time_array;
        }

        for(int i=0; i<numthreads ; i++){
            pthread_create(&threads[i], NULL, loadbalanced_approach,(void* )&thr[i]);
        }

        for(int j=0; j<numthreads; j++){
            pthread_join(threads[j],NULL);
        }

        for(int i=0; i<N; i++){
            if(num[i] == 1){
                //printf("%d ",i+1);
                fprintf(fptr, "%d ",i+1);
            }
        }
        fprintf(fptr, "\n");
        
        FILE *fptr1;
        fptr1 = fopen("./output/load_balanced_threadTime.txt","w");
        for(int i=0; i<numthreads; i++){
           fprintf(fptr1, "%d %lf\n",i+1,time_array[i]);
        }
        //fprintf(fptr1, "\n");
    
    return 0;
}
