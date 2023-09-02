#include "mathlib.h"

#include <stdio.h>

static int viete_num_terms = 0;

double pi_viete(void) {
    viete_num_terms = 0;
    double product = 1.0;
    double a = 0.0;
    double factor = a / 2;
    do {
        a = sqrt_newton(2.0 + a);
        factor = a / 2;
        product *= factor;
        viete_num_terms++;
    } while (absolute(1.0 - factor) > EPSILON);
    product = 2 / product;
    return product;
}

int pi_viete_factors(void) {
    return viete_num_terms;
}
