#include "mathlib.h"

#include <stdio.h>

static int e_num_terms = 2;

double e(void) {
    e_num_terms = 2;
    int k = 2;
    double prev_term = 1.0;
    double sum = 2.0;
    double curr_term = 1.0;
    do {
        prev_term = curr_term;
        curr_term = prev_term / k;
        sum += curr_term;
        k += 1;
        e_num_terms += 1;
    } while (absolute(curr_term) > EPSILON);
    return sum;
}

int e_terms(void) {
    return e_num_terms;
}
