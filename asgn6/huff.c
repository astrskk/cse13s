#include "bitwriter.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

uint64_t fill_histogram(Buffer *inbuf, double *histogram);
Node *create_tree(double *histogram, uint16_t *num_leaves);
void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length);
void huff_write_tree(BitWriter *outbuf, Node *node);
void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table);
void free_tree(Node *node);

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
        printf("After running ./huff you can include any of these flags\n-i <inputfile> "
               ":  Sets the name of the input file to inputfile\n-o <outputfile> : Sets "
               "the file to write to outputfile\n-h : Prints this help 	message.");
        return 0;
    }

    Buffer *inbuf = read_open(infile);
    if (inbuf == NULL) {
        fprintf(stderr, "infile not read");
        exit(1);
    }

    double *histogram = calloc(256, sizeof(double));
    uint64_t filesize = fill_histogram(inbuf, histogram);
    read_close(&inbuf);
    uint16_t num_leaves;
    Node *code_tree = create_tree(histogram, &num_leaves);
    //node_print_tree(code_tree, '<', 2);
    Code code_table[256];

    // printf("hello2\n");

    fill_code_table(code_table, code_tree, 0, 0);

    //  printf("hello\n");

    inbuf = read_open(infile);
    if (inbuf == NULL) {
        fprintf(stderr, "infile not read2");
        exit(1);
    }
    BitWriter *outbuf = bit_write_open(outfile);
    if (outbuf == NULL) {
        fprintf(stderr, "outfile not opened");
        exit(1);
    }
    huff_compress_file(outbuf, inbuf, filesize, num_leaves, code_tree, code_table);
    // printf("hello3");
    bit_write_close(&outbuf);
    read_close(&inbuf);
    free(histogram);
    free_tree(code_tree);
    // printf("hello4");
    return 0;
}

uint64_t fill_histogram(Buffer *inbuf, double *histogram) {
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }
    ++histogram[0x00];
    ++histogram[0xff];
    uint8_t byte = 0;
    uint64_t filesize = 0;
    while (read_uint8(inbuf, &byte)) {
        ++histogram[byte];
        ++filesize;
    }
    return filesize;
}

Node *create_tree(double *histogram, uint16_t *num_leaves) {
    PriorityQueue *pq = pq_create();
    uint16_t leaves = 0;
    for (int i = 0; i < 256; i++) {
        if (histogram[i] != 0) {
            Node *n = node_create((uint8_t) i, histogram[i]);
            enqueue(pq, n);
            leaves++;
        }
    }

    Node *left = NULL;
    Node *right = NULL;
    while (!pq_size_is_1(pq)) {
        if (!dequeue(pq, &left)) {
            fprintf(stderr, "left not work");
            exit(1);
        }
        if (!dequeue(pq, &right)) {
            fprintf(stderr, "right not work");
            exit(1);
        }
        Node *dollar_sign = node_create(0, left->weight + right->weight);
        dollar_sign->left = left;
        dollar_sign->right = right;
        enqueue(pq, dollar_sign);
    }
    Node *ret_val = NULL;
    dequeue(pq, &ret_val);
    *num_leaves = leaves;
    pq_free(&pq);
    return ret_val;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left && node->right) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left != NULL || node->right != NULL) {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    } else {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    }
}

void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, (uint8_t) 'H');
    bit_write_uint8(outbuf, (uint8_t) 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);

    uint8_t byte;
    while (read_uint8(inbuf, &byte)) {
        uint64_t code = code_table[byte].code;
        uint8_t code_length = code_table[byte].code_length;

        for (uint32_t i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, (code & 1));
            code >>= 1;
        }
    }
}

void free_tree(Node *node) {
    if (node != NULL) {
        if (node->left != NULL || node->right != NULL) {
            free_tree(node->left);
            free_tree(node->right);
            node_free(&node);
            node = NULL;
        }
    }
}
