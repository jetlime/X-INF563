#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1024

// Function to compare two strings lexicographically
int string_compare(const void *a, const void *b) {
    const char **sa = (const char **)a;
    const char **sb = (const char **)b;
    return strcmp(*sa, *sb);
}

// Function to rotate a string by one character
void rotate_string(char *str, int len) {
    char first = str[0];
    for (int i = 1; i < len; i++) {
        str[i - 1] = str[i];
    }
    str[len - 1] = first;
}

// Function to compute the output of the algorithm
void alg_c(char *S, int N, char **L, int *I) {
    // Allocate memory for the matrix M
    char **M = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        M[i] = (char *)malloc((N + 1) * sizeof(char));
    }

    // Generate the matrix M by cyclically shifting S
    // and sorting the rows lexicographically
    for (int i = 0; i < N; i++) {
        strcpy(M[i], S);
        rotate_string(S, N);
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