#include <stdlib.h>
#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int linsum(double *a, double *b, double *c, int i, int j, int n);
int mult(double *a, double *b, double *c, int n, int p, int m);

int linsum(double *a, double *b, double *c, int i, int j, int n) {
    double *sum = c + i*n + j;
    *sum = 0;
    for (int ii = 0; ii < n; ii++) {
        *sum += *(a + i*n + ii) * *(b + ii*n + j);
    }
    return 0;
}

int mult(double *a, double *b, double *c, int n, int p, int m) {
#pragma omp parallel
    for (int i = 0; i < n; i++) {
#pragma omp parallel
        for (int j = 0; j < m; j++) {
            linsum(a, b, c, i, j, p);
        }
    }
    return 0;
}

int main() {
    double *a;
    double *b;
    double *c;
    int n, m, p, pp;
    fread(&n, sizeof(int), 1, stdin);
    fread(&p, sizeof(int), 1, stdin);
    a = (double*) malloc (sizeof(double) * n * p);
    fread(a, sizeof(a), 1, stdin);
    fread(&pp, sizeof(int), 1, stdin);
    if (pp != p) {
        fprintf(stderr, "Matrix cannot be multiplied.\n");
        free(a);
        exit(1);
    }
    fread(&m, sizeof(int), 1, stdin);
    b = (double*) malloc (sizeof(int) * p * m);
    fread(b, sizeof(b), 1, stdin);
    c = (double*) malloc (sizeof(int) * n * m);
    mult(a, b, c, n, p, m);
    fwrite(&n, sizeof(int), 1, stdout);
    fwrite(&m, sizeof(int), 1, stdout);
    fwrite(&c, sizeof(c), 1, stdout);
    fprintf(stderr, "a: [%dx%d] size %ld\n", n, p, sizeof(a));
    fprintf(stderr, "b: [%dx%d] size %ld\n", n, p, sizeof(b));
    fprintf(stderr, "c: [%dx%d] size %ld\n", n, p, sizeof(c));
    free(a);
    free(b);
    free(c);

    return 0;
}

