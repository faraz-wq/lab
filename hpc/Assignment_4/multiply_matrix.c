/*
Installation and Running Instructions:

1. Install GCC compiler with OpenMP support:
   sudo apt update
   sudo apt install gcc

2. Compile the code with OpenMP flag:
   gcc matrix_mul_omp.c -o matrix_mul_omp -fopenmp

3. Run the executable:
   ./matrix_mul_omp

Reason for using OpenMP instead of CUDA:
- CUDA requires an NVIDIA GPU for running programs on GPU hardware.
- The current system does not have an NVIDIA GPU.
- OpenMP allows parallel programming on CPU cores without needing any special hardware.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 512

int main() {
    float *a, *b, *c;
    a = (float*)malloc(N * N * sizeof(float));
    b = (float*)malloc(N * N * sizeof(float));
    c = (float*)malloc(N * N * sizeof(float));

    for (int i = 0; i < N * N; i++) {
        a[i] = 1.0f;
        b[i] = 2.0f;
        c[i] = 0.0f;
    }

    #pragma omp parallel for collapse(2)
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            float sum = 0.0f;
            for (int k = 0; k < N; k++) {
                sum += a[row * N + k] * b[k * N + col];
            }
            c[row * N + col] = sum;
        }
    }

    printf("c[0] = %f\n", c[0]);
    printf("c[N*N-1] = %f\n", c[N*N-1]);

    free(a);
    free(b);
    free(c);

    return 0;
}