#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif

int main(int argc, char const *argv[]) {
    int n = 1000;
    int *a = (int*) malloc(sizeof(int) * n);
#pragma omp parallel for shared(a,n)
    for (int i = 0; i < n; i++) {
        a[i] = i+1;
    }
#pragma omp parallel
    {
        int tid = -1;
#ifdef _OPENMP
        tid = omp_get_thread_num();
#endif
        printf("Hello World: %d\n", tid);
    }
    char *vec = (char*) malloc (sizeof(char) * 6 * n);
    char word[16];
    strcpy(vec, "[ ");
    for (int i = 0; i < n-1; i++) {
        sprintf(word, "%d, ", a[i]);
        strcat(vec, word);
    }
    sprintf(word, "%d]", a[n-1]);
    strcat(vec, word);
    
    printf("a[@] = %s\n", vec);

    free(vec);
    free(a);
    return 0;
}
