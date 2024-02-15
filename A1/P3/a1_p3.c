#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void CountSortParallel(int a[], int n) {
    int i, j, count;
    int* temp = malloc(n * sizeof(int));

    #pragma omp parallel for private(i, j, count) shared(a, temp, n)
    for (i = 0; i < n; i++) {
        count = 0;

        #pragma omp parallel for reduction(+:count)
        for (j = 0; j < n; j++) {
            if (a[j] < a[i] || (a[j] == a[i] && j < i)) {
                count++;
            }
        }

        temp[count] = a[i];
    }

    memcpy(a, temp, n * sizeof(int));
    free(temp);
}

int main() {


    int arr[] = {4, 2, 7, 1, 5, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    CountSortParallel(arr, size);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}

/* Compile using commands:

gcc -fopenmp a1_p3.c -o a1_p3

./a1_p3

*/
