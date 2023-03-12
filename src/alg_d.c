#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <debug.h>

// Function to compare two strings lexicographically for simple strings
int string_compare(const void *a, const void *b) {
    const char *sa = (const char *)a;
    const char *sb = (const char *)b;
    return (*sa > *sb) - (*sa < *sb);
}
// Algorithm D: Decompression Algorithm
void alg_d(char **L, int *I, char **F) {
    DEBUG_PRINT("\nDecompression transformation debug trace: \n");

    int N = strlen(*L);
    
    strcpy(*F,*L); 
    // sort L
    qsort(*F, N, sizeof(char), string_compare);

    DEBUG_PRINT("F= %s\n",*F);

}