#include "shell.h"

#include "gaps.h"
#include "stats.h"

#include <stdio.h>
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t j = 0; j < GAPS; j++) {
        uint32_t g = gaps[j];
        for (uint32_t i = g; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, A[i]);
            while (j >= g && cmp(stats, temp, A[j - g]) < 0) {
                A[j] = move(stats, A[j - g]);
                j -= g;
            }
            A[j] = move(stats, temp);
        }
    }
}

//int main(void){
//	Stats stats;
//	uint32_t x[6] = {4, 1, 8, 3, 7, 9};
//	shell_sort(&stats, x, 6);
//	for (int i = 0; i < 6; i++){
//		printf("value; %d\n", x[i]);
//	}
//	return 0;
//}
