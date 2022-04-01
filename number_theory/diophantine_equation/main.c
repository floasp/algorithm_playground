#include <stdio.h>
#include <time.h>
#include <errno.h>

int main(){
    printf("Hello World!\n");
    
    clock_t begin = clock();

    errno = 0;
    FILE *file;
    file = fopen("output.dat", "w+");
    
    if(!file){
        printf("Error creating file.\n");
        printf("Error %d \n", errno);
        return 0;
    }

    long long counter = 0;

    for(long long a = 3; a < 5000; a++){
        for(long long b = 2; b < a; b++){
            for(long long c = 1; c <= b; c++){
                //if(c%100 == 0)
                    // printf("%d, %d, %d \n", a, b, c);
                // double result = a/(double)b+b/(double)c+c/(double)a;
                
                long long denominator = a*b*c;
                long long a_ac = a*a*c;
                long long b_ab = b*a*b;
                long long c_bc = c*b*c;
                long long sum = a_ac + b_ab + c_bc;
                // printf("%ld, %ld\n", denominator , sum);
                // printf("%ld, %ld, %ld\n", a_ac , b_ab, c_bc);
                
                // printf("%ld\n", sum % denominator);

                if(sum % denominator == 0){
                    long long result = sum / denominator;
                    printf("%ld, %ld, %ld, %ld \n", a, b, c, result);
                    fprintf(file, "%d, %d, %d, %d \n", a, b, c, result);
                }
                counter++;
                
                
                // if(result == (int)result){
                //     printf("%d, %d, %d, %d \n", a, b, c, (int)result);
                    
                // }
            }
        }
    }

    fclose(file);
    clock_t end = clock();
    
    double time = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("Runtime: %lfs\n", time);
    printf("Steps: %ld\n", counter);

    return 0;
}