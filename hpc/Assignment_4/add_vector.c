/*
Installation and Running Instructions:

1. Install GCC compiler with OpenMP support:
   sudo apt update
   sudo apt install gcc

2. Compile the code with OpenMP flag:
   gcc vector_add_omp.c -o vector_add_omp -fopenmp

3. Run the executable:
   ./vector_add_omp

Reason for using OpenMP instead of CUDA:
- CUDA requires an NVIDIA GPU for running programs on GPU hardware.
- The current system does not have an NVIDIA GPU.
- OpenMP allows parallel programming on CPU cores without needing any special hardware.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main() {
    float *a, *b, *c;
    a = (float*)malloc(N * sizeof(float));
    b = (float*)malloc(N * sizeof(float));
    c = (float*)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    printf("c[0] = %f\n", c[0]);
    printf("c[N-1] = %f\n", c[N-1]);

    free(a);
    free(b);
    free(c);

    return 0;
}