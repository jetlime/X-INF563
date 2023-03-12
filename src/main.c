#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <debug.h>

void alg_c(char *S, int N, char **L, int *I);
void alg_d(char **L, int *I);

int main() {
    char S[] = "abraca";
    int N = strlen(S);
    char *L = (char *)malloc(N * sizeof(char));
    int I;

    // Compression transformation (Algorithm C)
    alg_c(S, N, &L, &I);
    // Decompression transformation (Algorithm D)
    alg_d(&L, &I);

    printf("\n Compression transformation:\n");
    printf("L = %s\n", L);
    printf("I = %d\n", I);

    printf("\n Compression transformation:\n");
    printf("S = \n");

    free(L);
    return 0;
}