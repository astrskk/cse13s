#include "batcher.h"

#include "stats.h"

#include <stdio.h>
void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    if (cmp(stats, A[x], A[y]) > 0) {
        swap(stats, &A[x], &A[y]);
    }
}
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }

    uint32_t temp = n;
    uint32_t bit_length = 0;
    while (temp > 0) {
        temp = temp >> 1;
        bit_length++;
        //        printf("value of bit %i\nvalue of bitcounter: %i\n", temp, bit_length);
    }
    uint32_t t = bit_length;
    uint32_t p = 1 << (t - 1);

    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;

        while (d > 0) {
            for (uint32_t i = 0; i < (n - d); i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q = q >> 1;
            r = p;
        }
        p = p >> 1;
    }
}

//int main(void){
//	Stats stats;
//	uint32_t x[12] = {5, 2, 3, 1, 8, 10, 12, 11, 9, 7, 6, 4};
//	batcher_sort(&stats, x, 12);
//	for (int i = 0; i < 12; i++){
//		printf("value: %d\n", x[i]);
//	}
//	return 0;
//}
