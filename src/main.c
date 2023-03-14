#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

void alg_c(char *S, int N, char *L, int *I);
char* alg_d(char *L, int *I);

int main() {
    // read input file
    /*
    FILE* input_file = fopen("encode.txt", "r");
    if (!input_file)
        exit(EXIT_FAILURE);

    struct stat sb;
    if (stat("encode.txt", &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char* S = malloc(sb.st_size);
    fread(S, sb.st_size, 1, input_file);

    printf("%s\n", S);

    fclose(input_file);
    free(S);
    */

    char S[] = "information theory";
    int N = strlen(S);
    char *L = (char *)malloc(N * sizeof(char));
    int I;

    // Compression transformation (Algorithm C)
    alg_c(S, N, L, &I);
    // Decompression transformation (Algorithm D)
    char *S_revored = alg_d(L, &I);

    printf("\n Compression transformation:\n");
    printf("L = %s\n", L);
    printf("I = %d\n", I);

    printf("\n DeCompression transformation:\n");
    printf("S = %s\n",S_revored);

    free(L);
    free(S_revored);
    return 0;
}