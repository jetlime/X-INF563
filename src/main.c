#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "debug.h"

void alg_c(char *S, int N, char *L, int *I);
char* alg_d(char *L, int *I);

int main(){

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

    // Write the compressed elements in a file
    FILE *output_file = fopen("output.txt", "wb");
    if (output_file == NULL) {
        printf("Error: Failed to create output file.\n");
        return 1;
    }
    fprintf(output_file, "L: [%s]\n", L);
    fprintf(output_file,"I: %d\n",I);
    fclose(output_file);

    // Decompression transformation (Algorithm D)
    printf("\n-----------Step 06: Decompression Tranformation-----------\n\n");
    char *S_recovered = alg_d(L, &I);
    printf("\n\nS = %s\n",S_recovered);

    free(L);
    free(S_recovered);
    return 0;
}