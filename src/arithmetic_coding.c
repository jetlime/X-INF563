#include "arithmetic_coding.h"
#include "debug.h"

float *gen_intervals(int *R, int N, int *sz_of_prob) {
	int max=0;
	int i;

	for (i = 0; i < N; i++)
		if (R[i] > max) max = R[i];

	*sz_of_prob = max;
	float *cum_proba = (float *)calloc(max, sizeof(float));
	for (i = 0; i < N; i++)	cum_proba[R[i]]++;

	for (i = 0; i <= max; i++) {
		if (i != max) cum_proba[i+1] += cum_proba[i];
		cum_proba[i] /= N;
	}
	return cum_proba;
}

void scale_interval(float *cp, float *iv, int iv_sz, float low, float high) {
	float range = high - low;
	for (int i = 0; i <= iv_sz; i++) {
		iv[i] = low + cp[i] * range;
	}
}

float arith_encode(int *R, int N, float *cp, int cp_sz) {
	float lowbound = 0.0f;
	float highbound = 1.0f;

	float *subint = (float *)malloc(cp_sz * sizeof(float));
	for (int i = 0; i < N; i++) {
		scale_interval(cp, subint, cp_sz, lowbound, highbound);

		printf("lo: %f ", lowbound);
		for (int i = 0; i < cp_sz; i++) printf("%f ", subint[i]);
		printf("%f :hi\n", highbound);

		highbound = subint[R[i]];
		lowbound = R[i] ? subint[R[i]-1] : lowbound;
	}

	return (highbound + lowbound) / 2.0f;
}

int* arith_decode(float *cp, int cp_sz, int N, float coded_value) {
	float lowbound = 0.0f;
	float highbound = 1.0f;
    int* decoded_vector;
    decoded_vector=(int*)calloc(N, sizeof(int));
	for (int i = 0; i < N; i++) 
		decoded_vector[i]=-10;
	float *subint = (float *)malloc(cp_sz * sizeof(float));
	for (int i = 0; i < N; i++) {
		scale_interval(cp, subint, cp_sz, lowbound, highbound);

		printf("lo: %f ", lowbound);
		for (int i = 0; i < cp_sz; i++) printf("%f ", subint[i]);
		printf("%f :hi\n", highbound);
		int j = 0;
        for (j=0; coded_value > subint[j]; j++);
		highbound = subint[j];
		lowbound = j ? subint[j-1] : lowbound;
		decoded_vector[i]=j;
	}
	printf("\nDecoded vector R: ");
	for (int i = 0; i < N; i++) 
		printf("%i ", decoded_vector[i]);
	return decoded_vector;
}