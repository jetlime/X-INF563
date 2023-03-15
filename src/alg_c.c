#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

// Function to compare two strings lexicographically for array of strings
int string_compare_array(const void *a, const void *b) {
    char **sa = (char **)a;
    char **sb = (char **)b;
    return strcmp(*sa, *sb);
}

// Function to rotate a string by one character
void shift_cyclic(char *str, int N) {
    char first = str[0];
    for (int i = 1; i < N; i++) {
        str[i - 1] = str[i];
    }
    str[N - 1] = first;
}

void debug_print_matrix(char **M, int N){
    for (int row=0; row<N; row++)
    {
        for(int columns=0; columns<N; columns++)
        {
            DEBUG_PRINT("%c ", M[row][columns]);
        }
        if(row==0){
            DEBUG_PRINT("  | Row (0)  \n");
        }else{
            DEBUG_PRINT("  | %d  \n",row);
        }
    }
}

// Algorithm C: Compression Algorithm
void alg_c(char *S, int N, char *L, int *I) {
    // Allocate memory for the matrix M of size N by N
    char **M = (char **)malloc(N * sizeof(char *));
    
    // Allocate memory for each row of the matrix
    for (int i = 0; i < N; i++) {
        M[i] = (char *)malloc((N + 1) * sizeof(char));
    }

    // Generate the matrix M by cyclically shifting S
    for (int i = 0; i < N; i++) {
        strcpy(M[i], S);
        shift_cyclic(S, N);
    }
    
    DEBUG_PRINT("\nPrint Matrix M (unsorted):\n");
    debug_print_matrix(M, N);

    qsort(M, N, sizeof(char *), string_compare_array);

    DEBUG_PRINT("\nPrint Matrix M (sorted):\n");
    debug_print_matrix(M,N);
    
    // Find the index I of the row containing the original string S
    for (int i = 0; i < N; i++) {
        if (strcmp(M[i], S) == 0) {
            *I = i;
            break;
        }
    }

    // Extract the last column L of M
    for (int i = 0; i < N; i++) {
        L[i] = M[i][N - 1];
    }

    // Free the memory used by M
    for (int i = 0; i < N; i++) {
        free(M[i]);
    }
    free(M);
}