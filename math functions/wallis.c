#include "mathlib.h"

#include <stdio.h>

static int wallis_num_terms = 0;

double pi_wallis(void) {
    wallis_num_terms = 0;
    double k = 1.0;
    double product = 1.0;
    double factor = 1.0;
    double a = 0.0;
    double b = 0.0;
    do {
        a = 4.0 * (k * k);
        b = (4.0 * (k * k)) - 1.0;
        factor = a / b;
        product *= factor;
        wallis_num_terms++;
        k += 1.0;
    } while (absolute(1.0 - factor) > EPSILON);
    product *= 2.0;
    return product;
}

int pi_wallis_factors(void) {
    return wallis_num_terms;
}
