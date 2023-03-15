#include <stdlib.h>
#include <stdio.h>

float *gen_intervals(int *R, int N, int *sz_of_prob);
float arith_encode(int *R, int N, float *cp, int cp_sz);
int* arith_decode(float *cp, int cp_sz, int N, float coded_value);
void scale_interval(float *cp, float *iv, int iv_sz, float low, float high);