#include "io.h"

#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct buffer {
    int fd; // file descriptor from open() or creat()
    int offset; // offset into buffer a[]
        // next valid byte (reading)
        // next empty location (writing)
    int num_remaining;
    // number of bytes remaining in buffer (reading)

    uint8_t a[BUFFER_SIZE];
    // buffer
};

Buffer *read_open(const char *filename) {
    uint32_t fd = open(filename, O_RDONLY);
    if (fd < 0) {
        close(fd);
        return NULL;
    }
    Buffer *b = calloc(1, sizeof(Buffer));
    b->fd = fd;
    b->offset = 0;
    b->num_remaining = 0;
    return b;
}

void read_close(Buffer **pbuf) {
    close((*pbuf)->fd);
    if (pbuf != NULL && *pbuf != NULL) {
        free(*pbuf);
    }
    if (pbuf != NULL) {
        *pbuf = NULL;
    }
}

Buffer *write_open(const char *filename) {
    uint32_t fd = creat(filename, 0664);
    if (fd < 0) {
        close(fd);
        return NULL;
    }
    Buffer *b = calloc(1, sizeof(Buffer));
    b->fd = fd;
    b->offset = 0;
    b->num_remaining = 0;

    return b;
}

void write_close(Buffer **pbuf) {
    if (pbuf != NULL && *pbuf != NULL){
    	uint8_t *start = (*pbuf)->a;
    	uint32_t num_bytes = (*pbuf)->offset;
	    while (num_bytes > 0){
	    	ssize_t rc = write((*pbuf)->fd, start, num_bytes);
	    	if (rc < 0){
	    		fprintf(stderr, "write close error");
	    		exit(1);
	    	}
	    	start += rc;
	    	num_bytes -= rc;
    		}
    	close((*pbuf)->fd);
    	free(*pbuf);
    }
    if (pbuf != NULL) {
        *pbuf = NULL;
    }
}

bool read_uint8(Buffer *buf, uint8_t *x) {
    if (buf->num_remaining == 0) {
        ssize_t rc = read(buf->fd, buf->a, sizeof(buf->a));
        if (rc < 0) {
            fprintf(stderr, "rc < 0 error");
            exit(1);
        }
        if (rc == 0) {
            fprintf(stdout, "end of file");
            return false;
        }
        buf->num_remaining = rc;
        buf->offset = 0;
    }
    *x = buf->a[buf->offset];
    buf->offset++;
    buf->num_remaining--;
    return true;
}

bool read_uint16(Buffer *buf, uint16_t *x) {
    uint8_t a;
    uint8_t b;
    bool first_read = read_uint8(buf, &a);
    bool sec_read = read_uint8(buf, &b);
    if ((first_read && sec_read) == false) {
        return false;
    }
    uint16_t c = 0;
    c = b;
    c <<= 8;
    c |= a;
    *x = c;
    return true;
}

bool read_uint32(Buffer *buf, uint32_t *x) {
    uint16_t a;
    uint16_t b;
    bool first_read = read_uint16(buf, &a);
    bool sec_read = read_uint16(buf, &b);
    if ((first_read && sec_read) == false) {
        return false;
    }
    uint32_t c = 0;
    c += b;
    c <<= 16;
    c |= a;
    *x = c;
    return true;
}

void write_uint8(Buffer *buf, uint8_t x) {
    if (buf->offset == BUFFER_SIZE) {
        uint8_t *start = buf->a;
        int num_bytes = buf->offset;

        do {
            ssize_t rc = write(buf->fd, start, num_bytes);
            if (rc < 0) {
                fprintf(stderr, "error rc < 0");
                exit(1);
            }
            start += rc;
            num_bytes -= rc;
        } while (num_bytes > 0);
        
        buf->offset = 0;
    }
    buf->a[buf->offset] = x;
    buf->offset++;
    buf->num_remaining -= 1;
}

void write_uint16(Buffer *buf, uint16_t x) {
    write_uint8(buf, x);
    x >>= 8;
    write_uint8(buf, x);
}

void write_uint32(Buffer *buf, uint32_t x) {
    write_uint16(buf, x);
    x >>= 16;
    write_uint16(buf, x);
}
