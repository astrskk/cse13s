#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "aebmrvwnsh"

int main(int argc, char **argv) {
    int opt = 0;

    int arguments = 0;
    int i = 0;
    int a = 0;
    int e1 = 0;
    int b = 0;
    int m = 0;
    int r = 0;
    int v = 0;
    int w = 0;
    int n = 0;
    int s = 0;
    int h = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            a = 1;
            arguments = 1;
            i++;
            break;
        case 'e':
            e1 = 1;
            arguments = 1;
            i++;
            break;
        case 'b':
            arguments = 1;
            b = 1;
            i++;
            break;
        case 'm':
            arguments = 1;
            m = 1;
            i++;
            break;
        case 'r':
            arguments = 1;
            r = 1;
            i++;
            break;
        case 'v':
            v = 1;
            arguments = 1;
            i++;
            break;
        case 'w':
            w = 1;
            arguments = 1;
            i++;
            break;
        case 'n':
            n = 1;
            i++;
            arguments = 1;
            break;
        case 's':
            s = 1;
            arguments = 1;
            i++;
            break;
        case 'h':
            h = 1;
            arguments = 1;
            i++;
            break;
        }
    }
    char help_message[]
        = "By running mathlib-test.c, you can add 10 different options to the command to tell it "
          "which mathematical function you want to run.\nThese are the several different flags you "
          "can run. Make sure to run it in the format of ./mathlib-test -<flag> -<flag2> ..:\n-a : "
          "Runs all tests.\n-e : Runs e approximation test.\n-b : Runs Bailey-Borwein-Plouffe "
          "approximation test.\n-m : Runs Madhava approximation test.\n-r : Runs Euler sequence "
          "approximation test.\n-v : Runs Viete approximation test.\n-w : Runs Wallis "
          "approximation test.\n-n : Runs Newton-Raphson square root approximation tests, calling "
          "sqrt newton() with various inputs for testing. This option does not require any "
          "parameters, and will only test within the range of [0, 10) (it will not test the value "
          "10).\n-s : Enable printing of statistics to see computed terms and factors for all "
          "tested functions.\n-h : Displays this help message.\n";
    if (s && i == 1) {
        printf("%s", help_message);
        return 0;
    }
    if (h) {
        printf("%s", help_message);
        return 0;
    }
    if (a) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, M_E - e());
        if (s) {
            printf("e() terms = %d\n", e_terms());
        }
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            M_PI - pi_bbp());
        if (s) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            M_PI - pi_madhava());
        if (s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            M_PI - pi_madhava());
        if (s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            M_PI - pi_viete());
        if (s) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
        printf("pi_wallis() = %16.15lf, M_PI, %16.15lf, diff = %16.15lf\n", pi_wallis(), M_PI,
            M_PI - pi_wallis());
        if (s) {
            printf("pi_wallis() terms = %d\n", pi_wallis_factors());
        }
        for (double i = 0.0; i <= 9.95; i += 0.1) {
            printf("sqrt_newton(%.2lf) = %16.15lf, sqrt(%.2lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), sqrt(i) - sqrt_newton(i));
            if (s) {
                printf("sqrt_newton_iters() = %d\n", sqrt_newton_iters());
            }
        }
        return 0;
    }
    if (e1) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, M_E - e());
        if (s) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (b) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            M_PI - pi_bbp());
        if (s) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    if (m) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            M_PI - pi_madhava());
        if (s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    if (r) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            M_PI - pi_euler());
        if (s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (v) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            M_PI - pi_viete());
        if (s) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    if (w) {
        printf("pi_wallis() = %16.15lf, M_PI, %16.15lf, diff = %16.15lf\n", pi_wallis(), M_PI,
            M_PI - pi_wallis());
        if (s) {
            printf("pi_wallis() terms = %d\n", pi_wallis_factors());
        }
    }
    if (n) {
        for (double i = 0.0; i <= 9.95; i += 0.1) {
            printf("sqrt_newton(%.2lf) = %16.15lf, sqrt(%.2lf) = %16.15lf, diff = %16.15lf\n", i,
                sqrt_newton(i), i, sqrt(i), sqrt(i) - sqrt_newton(i));
            if (s) {
                printf("sqrt_newton_iters() = %d\n", sqrt_newton_iters());
            }
        }
    }
    if (arguments == 0) {
        printf("%s", help_message);
    }
    return 0;
}
