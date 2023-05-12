#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "aishqbr:n:p:H"

int main(int argc, char **argv) {

    enum sorts { insert = 0, shell, heap, quick, batcher };
    char *sort_names[]
        = { "Insertion Sort", "Shell Sort", "Heap Sort", "Quick Sort", "Batcher Sort" };
    int opt = 0;

    Set set = set_empty();
    Stats stats;

    int help = 0;

    uint32_t seed = 13371453;
    uint32_t size = 100;
    uint32_t num_elems = 100;
    int args = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            for (int i = 0; i < 5; i++) {
                set = set_insert(set, i);
            }
            args = 1;
            break;
        case 'i':
            set = set_insert(set, 0);
            args = 1;
            break;
        case 's':
            set = set_insert(set, 1);
            args = 1;
            break;
        case 'h':
            set = set_insert(set, 2);
            args = 1;
            break;
        case 'q':
            set = set_insert(set, 3);
            args = 1;
            break;
        case 'b':
            set = set_insert(set, 4);
            args = 1;
            break;
        case 'r':
            seed = (uint32_t) strtoull(optarg, NULL, 10);
            args = 1;
            break;
        case 'n':
            size = (uint32_t) strtoull(optarg, NULL, 10);
            args = 1;
            break;
        case 'p':
            num_elems = (uint32_t) strtoull(optarg, NULL, 10);
            args = 1;
            break;
        case 'H':
            help = 1;
            args = 1;
            break;
        }
    }
    if (num_elems > size) {
        num_elems = size;
    }
    srandom((unsigned) seed);

    if (help || args == 0) {
        printf("By running './sorting <flag1> <flag2> ..' you can input the following flags to "
               "tell the program which sorting algorithmy you want to run and change the size, "
               "seed, and if you want to print the number of elements or not:\n-a : Employs all "
               "sorting algorithms\n-i : Enables Insertion Sort\n-s : Enables Shell Sort\n-h : "
               "Enables Heap Sort\n-q : Enables Quick Sort\n-b : Enables Batcher Sort\n-r <num> : "
               "Sets	the seed to num. The default seed is 13371453\n-n <num> : Sets the size of "
               "array to num. The default size is 100\n-p <elements> : Enables printing of "
               "statistics to see computed terms and factors for all tested functions, elements is "
               "the number of computed terms\n-h : Displays this help message again\n");
        return 0;
    }

    int sorted = 0;

    //	printf("%u", set);
    if (set) {
        for (int i = insert; i <= batcher; i++) {
            if (set_member(set, i)) {
                reset(&stats);
                uint32_t *list = malloc(size * sizeof(uint32_t));
                for (uint32_t i = 0; i < size; i++) {
                    list[i] = ((uint32_t) random() & 0x3FFFFFFF);
                }
                //			for (uint32_t i = 0; i < size; i++) {
                //				printf("%u", list[i]);
                //			}
                if (i == insert) {
                    insertion_sort(&stats, list, size);
                    sorted = 1;
                    print_stats(&stats, sort_names[i], num_elems);
                } else if (i == shell) {
                    shell_sort(&stats, list, size);
                    sorted = 1;
                    print_stats(&stats, sort_names[i], num_elems);
                } else if (i == heap) {
                    heap_sort(&stats, list, size);
                    sorted = 1;
                    print_stats(&stats, sort_names[i], num_elems);
                } else if (i == quick) {
                    quick_sort(&stats, list, size);
                    sorted = 1;
                    print_stats(&stats, sort_names[i], num_elems);
                } else if (i == batcher) {
                    batcher_sort(&stats, list, size);
                    sorted = 1;
                    print_stats(&stats, sort_names[i], num_elems);
                }
                if (sorted) {
                    for (uint32_t e = 0; e < num_elems; e++) {
                        if (e % 5 == 0 && e != 0) {
                            printf("\n");
                        }
                        printf("%13" PRIu32, list[e]);
                    }
                }
                sorted = 0;
                free(list);
                printf("\n");
            }
        }
    }
    return 0;
}
