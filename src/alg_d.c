#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"

void debug_print_array(int *T, int N){
    for (int row=0; row<N; row++)
    {
        printf("%d ", T[row]);   
    }
}
// Function to compare two strings lexicographically for simple strings
int string_compare(const void *a, const void *b) {
    const char *sa = (const char *)a;
    const char *sb = (const char *)b;
    return (*sa > *sb) - (*sa < *sb);
}

void first_rotation_char(int N, char *L ,char *F){
    strcpy(F,L); 
    // sort L
    qsort(F, N, sizeof(char), string_compare);
    printf("F= %s\n",F);
}

void compute_T(int N, char *F, int *T,char *L){
    for (int j = 0; j < N; j++) {
        char ch = L[j];
        // find the k'th occurence
        int k = 1;
        for(int i=0; i<j;i++){
            if(L[i]==ch){
                k++;
            }
        }
        // find the k'th instance of ch in F
        int k_2 = 1 ;
        for (int i=0; i<N;i++){
            if(F[i]==ch){
                if(k_2 == k){
                    T[j] = i;
                    break;
                }else{
                    k_2++;
                }
            }
        }
    }

    printf("T = ");
    debug_print_array(T,N);
}

int compute_T_recursion(int i, int x,int *T) {
    if (i == 0) {
        return x;
    }else{
        return T[compute_T_recursion(i-1,x,T)];
    }
}

void compute_S(int N,int *I,char *S, char *L, int *T){
    for(int i=0;i<N;i++)
    {
        // compute T^i[x]
        int index = compute_T_recursion(i,*I,T);
        S[N-1-i] = L[index];
    }
}

// Algorithm D: Decompression Algorithm
char *alg_d(char *L, int *I) {
    int N = strlen(L);
    char *F = (char *)malloc(N * sizeof(char));
    int *T = (int *)malloc(N* sizeof(int));
    char *S = (char *)malloc(N * sizeof(char));

    // D1. find first characters of rotations
    first_rotation_char(N, L,F);

    // D2. build list of predecessor characters
    compute_T(N,F,T,L);

    // D3. form string S
    compute_S(N,I,S,L,T);
    
    free(F);
    free(T);

    return S;
}