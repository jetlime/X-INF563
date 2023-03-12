#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <debug.h>

void debug_print_array(int *T, int N){
    for (int row=0; row<N; row++)
    {
        DEBUG_PRINT("%d     ", T[row]);   
    }
}
// Function to compare two strings lexicographically for simple strings
int string_compare(const void *a, const void *b) {
    const char *sa = (const char *)a;
    const char *sb = (const char *)b;
    return (*sa > *sb) - (*sa < *sb);
}

void first_rotation_char(int N, char ***L ,char **F){
    strcpy(*F,**L); 
    // sort L
    qsort(*F, N, sizeof(char), string_compare);
    DEBUG_PRINT("F= %s\n",*F);
}

void compute_T(int N, char **F, int **T,char ***L){
    for (int j = 0; j < N; j++) {
        char ch = (**L)[j];
        // find the k'th occurence
        int k = 1;
        for(int i=0; i<j;i++){
            if((**L)[i]==ch){
                k++;
            }
        }
        // find the k'th instance of ch in F
        int k_2 = 1 ;
        for (int i=0; i<N;i++){
            if((*F)[i]==ch){
                if(k_2 == k){
                    (*T)[j] = i;
                    break;
                }else{
                    k_2++;
                }
            }
        }
    }
    debug_print_array(*T,N);
}

// Algorithm D: Decompression Algorithm
void alg_d(char **L, int *I) {
    DEBUG_PRINT("\nDecompression transformation debug trace: \n");

    int N = strlen(*L);
    char *F = (char *)malloc(N * sizeof(char));
    int *T = (int *)malloc(N* sizeof(int));

    // D1. find first characters of rotations
    first_rotation_char(N, &L,&F);

    // D2. build list of predecessor characters
    compute_T(N,&F,&T,&L);

    free(F);
    free(T);
}