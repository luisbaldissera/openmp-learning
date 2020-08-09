/*
 * Matrix Generator
 *
 * A random double type matrix generator using OpenMP
 * for parallel. To compile, use:
 *
 * gcc -o matGen -fopen marGen.c
 *
 * Usage: matGen <n> <m>
 *
 * @author luisbaldissera
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#define APP_NAME "matGen"

int generate_matrix(double *dest, int n, int m) {
    int size = n * m;
#pragma omp parallel for shared(dest,size)
    for (int i = 0; i < size; i++) {
        *(dest + i) = (double) rand();
    }
}

int main(int argc, char const *argv[]){ 
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <n> <m>\n", APP_NAME);
        exit(1);
    }
    srand(time(NULL));
    int n, m;
    double *a;
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    a = (double*) calloc(sizeof(double), n * m);
    fprintf(stderr, "generating matrix %dX%d\n", n, m);
    generate_matrix(a, n, m);
    fwrite(&n, sizeof(int), 1, stdout);
    fwrite(&m, sizeof(int), 1, stdout);
    fwrite(a, sizeof(double), n*m, stdout);

    free(a);

    return 0;
}
