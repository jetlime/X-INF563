#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "debug.h"
#include "move_to_front.h"

void alg_c(char *S, int N, char *L, int *I);
char* alg_d(char *L, int *I);

int main() {
    // read from file
    struct stat sb;
    if (stat("input.txt", &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    FILE *input_file = fopen("input.txt", "rb");
    if (input_file == NULL) {
        printf("Error: Failed to open the file.\n");
        return 1;
    }

    // Read the text from the file into S
    char S[sb.st_size];
    if (fread(S, sb.st_size, 1,input_file)< 1) {
        printf("Error: Failed to read the file.\n");
        fclose(input_file);
        return 1;
    }
    // remove EOF byte
    S[sb.st_size] = '\0';
    
    // Close the file
    fclose(input_file);
    
    printf("-----------Step 01: Compression Tranformation-----------\n\n");
    printf("S = %s\n",S);
    int N = strlen(S);
    printf("N = %d\n",N);
    char *L = (char *)malloc(N * sizeof(char));
    int I;

    // Compression transformation (Algorithm C)
    alg_c(S, N, L, &I);
    printf("L = %s\n", L);
    printf("I = %d\n", I);

    printf("\n-----------Step 02: Move-to-front Encoding-----------\n\n");
    char *Y = gen_alpha(L,N);
    int Ylen = strlen(Y);
    char *Ycp = (char *)calloc(Ylen, 1); 
    memcpy(Ycp, Y, Ylen);
    int *R = move_to_front_enc(L, Ycp, N);
    printf("R = ");
    for (int i = 0; i < N; i++) printf("%i ", R[i]);
    putchar('\n');

    printf("\n-----------Step 05: Move-to-front Decoding-----------\n\n");
    memcpy(Ycp, Y, Ylen);
    char *dec = move_to_front_dec(R, Ycp, N);
    printf("%s\n", dec);

    // Decompression transformation (Algorithm D)
    printf("\n\n-----------Step 06: Decompression Tranformation-----------\n\n");
    char *S_revored = alg_d(L, &I);
    printf("\nS = %s\n",S_revored);

    free(L);
    free(S_revored);
    return 0;
}