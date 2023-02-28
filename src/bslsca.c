#include <stdio.h>

sort_rotations(const char* s, int* n, int* i ){
    int N = strlen(s);
    char** shifts = (char**) malloc(N * sizeof(char*));

    for (int k = 0; k < N; k++) {
        shifts[k] = (char*) malloc((N) * sizeof(char));
        shifts[k][0] = s[N]
        for (int j = 0; j < N; j++) {
            shifts[k][j] = s[(k + j) % N];
        }
        shifts[k][N] = '\0';
        
    }
}


int main(int argc, char *argv[]) {
    char s[100];
    printf("Enter a string: ");
    scanf("%s", s);
    int n, i;

    char** shifts = cyclic_shifts(s, &n, &i);
    // find the row equal to s
    if (strcmp(shifts[k], s) == 0) {
            *i = k;
        }
    return 0;
}