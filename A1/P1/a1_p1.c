#include <stdio.h>
#include <omp.h>

int main() {
    int num_threads, num_iterations;


    printf("Enter number of iterations: ");
    scanf("%d", &num_iterations);


    #pragma omp parallel
    {
        #pragma omp master
        {
            num_threads = omp_get_num_threads();
            printf("Using %d threads.\n", num_threads);
        }
    }


    #pragma omp parallel for
    for (int i = 0; i < num_iterations; ++i) {
        int thread_id = omp_get_thread_num();
        printf("Thread %d: Iteration %d\n", thread_id, i);
    }

    return 0;
}

/* Compile using commands:

gcc -fopenmp a1_p1.c -o a1_p1

./a1_p1

*/
