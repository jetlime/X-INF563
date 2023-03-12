#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG 0
#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)    /* Don't do anything in release builds */
#endif

// Function to compare two strings lexicographically
int string_compare(const void *a, const void *b) {
    const char **sa = (const char **)a;
    const char **sb = (const char **)b;
    return strcmp(*sa, *sb);
}

// Function to rotate a string by one character
void shift_cyclic(char *str, int len) {
    char first = str[0];
    for (int i = 1; i < len; i++) {
        str[i - 1] = str[i];
    }
    str[len - 1] = first;
}

// Algorithm C: Compression Algorithm
void alg_c(char *S, int N, char **L, int *I) {

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
    for (int row=0; row<N; row++)
    {
        for(int columns=0; columns<N; columns++)
        {
            DEBUG_PRINT("%c     ", M[row][columns]);
        }
        printf("\n");
    }

    qsort(M, N, sizeof(char *), string_compare);

    // Find the index I of the row containing the original string S
    for (int i = 0; i < N; i++) {
        if (strcmp(M[i], S) == 0) {
            *I = i;
            break;
        }
    }

    // Extract the last column L of M
    for (int i = 0; i < N; i++) {
        (*L)[i] = M[i][N - 1];
    }

    // Free the memory used by M
    for (int i = 0; i < N; i++) {
        free(M[i]);
    }
    free(M);
}