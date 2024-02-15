#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long long int total_tosses, number_in_circle = 0;


    printf("Enter number of tosses: ");
    scanf("%lld", &total_tosses);


    int num_threads = omp_get_max_threads();
    printf("Using %d threads.\n", num_threads);


    unsigned int seed = 42;


    #pragma omp parallel for reduction(+:number_in_circle) private(seed)
    for (long long int toss = 0; toss < total_tosses; ++toss) {

        double x = (2.0 * (rand_r(&seed) / (double)RAND_MAX)) - 1.0;
        double y = (2.0 * (rand_r(&seed) / (double)RAND_MAX)) - 1.0;


        double distance_squared = x * x + y * y;


        if (distance_squared <= 1.0) {
            number_in_circle++;
        }
    }


    double pi_estimate = 4.0 * number_in_circle / (double)total_tosses;


    printf("Value of pi: %lf\n", pi_estimate);

    return 0;
}


/* Compile using commands:

gcc -fopenmp a1_p2.c -o a1_p2

./a1_p2

*/
