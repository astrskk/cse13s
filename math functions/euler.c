#include "mathlib.h"

#include <stdio.h>

static int euler_num_terms = 1;

double pi_euler(void) {

    euler_num_terms = 1;
    double k = 2.0;
    double curr_term = 1.0;
    double sum = 1.0;

    do {
        curr_term = 1.0 / ((k * k));
        sum += curr_term;
        k += 1.0;
        euler_num_terms += 1;
    } while (absolute(curr_term) > EPSILON);

    sum = sqrt_newton(6.0 * sum);
    return sum;
}

int pi_euler_terms(void) {
    return euler_num_terms;
}
