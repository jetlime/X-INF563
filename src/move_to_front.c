#include "move_to_front.h"
#include <stdio.h>

char *gen_alpha(char *str, int len) {
	int j = 0, sz = 64;
	char *alpha = (char *)calloc(sz, 1);
	char *tmp;

	for (int i = 0; i < len; i++) {
		if (!strchr(alpha, str[i])) {
			if (j > sz) {
				sz = sz+32;
				tmp = calloc(sz, 1);
				memcpy(tmp, alpha, j);
				free(alpha);
				alpha = tmp;
			}
			alpha[j++] = str[i];
		}
	}
	// return a packed alpha
	return realloc(alpha, j+1);
}

void bring_to_front(char *str, int idx) {
	char tmp = str[idx];
	while (idx > 0) {
		str[idx] = str[idx-1];
		idx--;
	}
	str[idx] = tmp;
}

int find_int_idx(int *arr, int len, int target) {
	int i = 0;
	while (i < len) {
		if (*arr == target) return i;
		arr++; i++;
	}
	return -1;
}

int *move_to_front_enc(char *L, char *Y, int N) {
	int *R;
	int i;

	R = (uint *)malloc(N * sizeof(unsigned int));
	for (i = 0; i < N; i++) {
		R[i] = strchr(Y, L[i]) - Y;
		bring_to_front(Y, R[i]);
	}

	return R;
}

char *move_to_front_dec(int *R, char *Y, int N) {
	char *L = (char *)malloc(N);
	for (int i = 0; i < N; i++) {
		L[i] = Y[R[i]];
	    bring_to_front(Y, R[i]);
	}
	return L;
}

/* int main() { */
/* 	char *L = "caraab"; */
/* 	int N = strlen(L); */
/* 	char *Y = gen_alpha(L, N); */
/* 	/\* char Y[5] = { 'a', 'b', 'c', 'r', '\0' }; *\/ */
/* 	int Ylen = strlen(Y); */
/* 	char *Ycp = (char *)calloc(Ylen, 1); */
/* 	memcpy(Ycp, Y, Ylen); */

/* 	int *enc = move_to_front_enc(L, Ycp, N); */
/* 	for (int i = 0; i < N; i++) printf("%i ", enc[i]); */
/* 	putchar('\n'); */

/* 	memcpy(Ycp, Y, Ylen); */
/* 	char *dec = move_to_front_dec(enc, Ycp, N); */
/* 	printf("%s\n", dec); */
	
/* 	return 0; */
/* } */
