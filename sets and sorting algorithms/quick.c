#include "quick.h"

#include "stats.h"

#include <stdio.h>
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;
    for (uint32_t j = lo; j < hi; j++) {
        if (cmp(stats, A[j - 1], A[hi - 1]) < 0) {
            i++;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (cmp(stats, lo, hi) < 0) {
        uint32_t p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}

//int main(void){
//	uint32_t x[6] = {4, 1, 6, 7, 3, 2};
//	Stats stats;
//	quick_sort(&stats, x, 6);
//	for (int i = 0; i < 6; i++){
//		printf("value %d\n", x[i]);
//	}
//}
