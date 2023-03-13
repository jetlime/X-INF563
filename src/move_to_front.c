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

int *move_to_front(char *L, int N) {
	int *R;
	int i;

	char *Y = gen_alpha(L, N);
	R = (uint *)malloc(N * sizeof(unsigned int));
	for (i = 0; i < N; i++) {
		R[i] = strchr(Y, L[i]) - Y;
		bring_to_front(Y, R[i]);
	}

	free(Y);
	return R;
}
