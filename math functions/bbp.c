#include "mathlib.h"

#include <stdio.h>

static int bbp_num_terms = 1;

double pi_bbp(void) {

    bbp_num_terms = 1;
    double first_term = (4.0 - (26.0 / 30.0));
    double k = 1.0;
    double curr_term = first_term;
    double sum = curr_term;
    double a = 1.0;
    double b = 1.0;
    do {
        a *= 1.0 / 16.0;
        b = ((4.0 / ((8.0 * k) + 1)) - (2.0 / ((8.0 * k) + 4)) - (1.0 / ((8.0 * k) + 5.0))
             - (1.0 / ((8.0 * k) + 6.0)));
        curr_term = a * b;
        sum += curr_term;
        k += 1.0;
        bbp_num_terms++;
    } while (absolute(curr_term) > EPSILON);
    return sum;
}

int pi_bbp_terms(void) {
    return bbp_num_terms;
}
