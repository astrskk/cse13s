#include "insert.h"

#include "stats.h"

#include <stdio.h>

void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    for (uint32_t k = 1; k < length; k++) {
        uint32_t j = k;
        uint32_t temp = move(stats, arr[k]);
        while (j > 0 && cmp(stats, temp, arr[j - 1]) < 0) {
            arr[j] = move(stats, arr[j - 1]);
            j--;
        }
        arr[j] = move(stats, temp);
    }
}

//int main(void){
//	uint32_t x[6] = {4, 1, 8, 3, 7, 9};
//	Stats stats;
//	insertion_sort(&stats, x, 6);
//	for (int i = 0; i < 6; i++){
//		printf("%d\n", x[i]);
//	}
//	return 0;
//}
