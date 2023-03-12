#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <debug.h>

void alg_c(char *S, int N, char **L, int *I);
char* alg_d(char **L, int *I);

int main() {
    char S[] = ">#<Using the BWT as a front end for data compression has a result similar to that of simple statistical modeling programs.Paul was here. This is a test>#<";
    int N = strlen(S);
    char *L = (char *)malloc(N * sizeof(char));
    int I;

    // Compression transformation (Algorithm C)
    alg_c(S, N, &L, &I);
    // Decompression transformation (Algorithm D)
    char *S_revored = alg_d(&L, &I);

    printf("\n Compression transformation:\n");
    printf("L = %s\n", L);
    printf("I = %d\n", I);

    printf("\n DeCompression transformation:\n");
    printf("S = %s\n",S_revored);

    free(L);
    free(S_revored);
    return 0;
}