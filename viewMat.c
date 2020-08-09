/*
 * Matrix Viewer
 *
 * A simple viewer for matrix generated in raw data
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
#include <string.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
    int n, m;
    double *a;
    fread(&n, sizeof(int), 1, stdin);
    fread(&m, sizeof(int), 1, stdin);
    a = (double*) calloc(sizeof(double), n*m);
    fread(a, sizeof(double), n*m, stdin);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            double x = *(a + i*m + j);
            printf("\t%lf", x);
        }
        printf("\n");
    }
    return 0;
}
