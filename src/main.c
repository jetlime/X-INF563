#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "move_to_front.h"
#include "arithmetic_coding.h"
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

    printf("\n-----------Step 02: Move-to-front Encoding-----------\n\n");
    char *Y = gen_alpha(L,N);
    int Ylen = strlen(Y);
    char *Ycp = (char *)calloc(Ylen, 1); 
    memcpy(Ycp, Y, Ylen);
    int *R = move_to_front_enc(L, Ycp, N);
    printf("L = ");
    for (int i = 0; i < N; i++) printf("%d ", R[i]);
    printf("(Encoded with move-to-front)\n");

    printf("\n-----------Step 03: Arithmetic Encoding-----------\n\n");
        
	int cp_sz;

	float *cp = gen_intervals(R, N, &cp_sz);
    printf("Coding Model:  ");
	for (int i = 0; i <= cp_sz; i++) printf("%f ", cp[i]);
    printf("\n\n");
	float OUT=arith_encode(R, N, cp, cp_sz);
 	printf("\nEncoding: %f\n", OUT);

    // Write the compressed elements in a file
    FILE *output_file = fopen("output.txt", "wb");
    if (output_file == NULL) {
        printf("Error: Failed to create output file.\n");
        return 1;
    }
    // fwrite(OUT, strlen(OUT), 1, output_file);
    fprintf(output_file, "OUT: [%f]\n", OUT);
    fprintf(output_file,"I: %d\n",I);
    fprintf(output_file,"N: %d\n",N);
    fprintf(output_file,"Y: [%s]\n", Y);
    fprintf(output_file,"Arithmetic Encoding header:\n Coding Model: ");
    for (int i = 0; i <= cp_sz; i++) fprintf(output_file,"%f, ", cp[i]);
    fclose(output_file);

    printf("\n-----------Step 04: Arithmetic Decoding-----------\n\n");

	int* decoded_R;
    decoded_R = (int*)calloc(N, sizeof(int));
	decoded_R = arith_decode(cp, cp_sz, N, OUT);

    printf("\n\n-----------Step 05: Move-to-front Decoding-----------\n\n");
    memcpy(Ycp, Y, Ylen);
    char * decoded_L = (char *)malloc(N * sizeof(char));
    decoded_L = move_to_front_dec(decoded_R, Ycp, N);
    printf("L = %s\n", L);

    // Decompression transformation (Algorithm D)
    printf("\n-----------Step 06: Decompression Tranformation-----------\n\n");
    char *S_revored = alg_d(decoded_L, &I);
    printf("\n\nS = %s\n",S_revored);

    free(L);
    free(S_revored);
    free(decoded_L);
    free(decoded_R);
    return 0;
}