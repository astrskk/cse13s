#include "bmp.h"
#include "io.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    char *infile = NULL;
    char *outfile = NULL;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = optarg;
            if (infile == NULL) {
                printf("infile broke");
            }
            assert(infile != NULL);
            break;
        case 'o':
            outfile = optarg;
            if (outfile == NULL) {
                printf("outfile broke");
            }
            assert(outfile != NULL);
            break;
        case 'h': help = true; break;
        }
    }

    if (help) {
        fprintf(stdout, "After running ./colorb you can include any of these flags\n-i <inputfile> "
                        ":  Sets the name of the input file to inputfile\n-o <outputfile> : Sets "
                        "the file to write to outputfile\n-h : Prints this help 	message.");
    }

    Buffer *read_buffer = read_open(infile);
    if (read_buffer == NULL) {
        fprintf(stderr, "input file broke");
        exit(1);
    }

    BMP *bmp = bmp_create(read_buffer);
    read_close(&read_buffer);

    if (bmp == NULL) {
        fprintf(stderr, "bmp creation failed");
        exit(1);
    }

    bmp_reduce_palette(bmp);

    Buffer *write_buffer = write_open(outfile);
    if (write_buffer == NULL) {
        fprintf(stderr, "output file broke");
        exit(1);
    }

    bmp_write(bmp, write_buffer);

    write_close(&write_buffer);
    bmp_free(&bmp);
    return 0;
}
