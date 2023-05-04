#include "mathlib.h"

#include <stdio.h>

static int madhava_num_terms = 1;

double pi_madhava(void) {
    madhava_num_terms = 1;
    double coeff = 12.0;
    double sqrt_12 = sqrt_newton(coeff);

    double a = 1.0;
    double k = 1;
    double sum = 1.0;
    double curr_term = 1.0;
    do {
        a *= (1.0 / -3.0);
        curr_term = a * (1.0 / ((2.0 * k) + 1.0));
        sum += curr_term;
        k += 1.0;
        madhava_num_terms += 1;
    } while (absolute(curr_term) > EPSILON);
    sum *= sqrt_12;
    return sum;
}

int pi_madhava_terms(void) {
    return madhava_num_terms;
}
