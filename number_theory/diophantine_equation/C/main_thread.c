#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>

#define N_CORES 1
#define N 5000

FILE *file;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *calculateBatch(void *vargp){

    int batch = *(int *)vargp;

    for(long long a = 3 + batch; a < N; a+=N_CORES){
        for(long long b = 2; b < a; b++){
            for(long long c = 1; c <= b; c++){
                
                long long denominator = a*b*c;
                long long a_ac = a*a*c;
                long long b_ab = b*b*a;
                long long c_bc = c*b*c;
                long long sum = a_ac + b_ab + c_bc;

                if(sum % denominator == 0){
                    long long result = sum / denominator;
                    pthread_rwlock_wrlock(&rwlock);
                    printf("%ld, %ld, %ld, %ld \n", a, b, c, result);
                    fprintf(file, "%d, %d, %d, %d \n", a, b, c, result);
                    pthread_rwlock_unlock(&rwlock);
                }
            }
        }
    }


    return NULL;
}

int main(){
    printf("Hello World!\n");
    
    struct timeval start, end;
    // struct timespec g_begin, g_end;
    gettimeofday(&start, NULL);
    // clock_t c_begin = clock();
    // time_t t_begin = time(NULL);

    errno = 0;
    file = fopen("output.dat", "w+");
    
    if(!file){
        printf("Error creating file.\n");
        printf("Error %d \n", errno);
        return 0;
    }

    int batch_nrs[N_CORES];

    for(int i = 0; i < N_CORES; i++){
        batch_nrs[i] = i;
    }

    pthread_t tid[N_CORES];
    for (int i = 0; i < N_CORES; i++){
        pthread_create(&tid[i], NULL, calculateBatch, (void *)&batch_nrs[i]);
    }
    for (int i = 0; i < N_CORES; i++){
       pthread_join(tid[i], NULL);
    }
    

    fclose(file);
    gettimeofday(&end, NULL);
    // clock_t c_end = clock();
    // time_t t_end = time(NULL);

    // double time = (double)(c_end-c_begin) / CLOCKS_PER_SEC;
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = (end.tv_usec) - (start.tv_usec);
    double time_ = seconds + (double)micros / 1000000;
    // printf("Runtime: %lfs\n", time);
    printf("Runtime: %lfs\n", time_);
    // printf("Runtime with time is %d seconds", (t_end - t_begin));

    return 0;
}