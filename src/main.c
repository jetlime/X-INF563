#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alg_c(char *S, int N, char **L, int *I);

int main() {
    char S[] = "abraca";
    int N = strlen(S);
    char *L = (char *)malloc(N * sizeof(char));
    int I;

    alg_c(S, N, &L, &I);

    printf("L = %s\n", L);
    printf("I = %d\n", I);

    free(L);
    return 0;
}