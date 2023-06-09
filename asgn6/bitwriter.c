#include "io.h"
#include "bitwriter.h"
#include <stdio.h>
#include <stdlib.h>
struct BitWriter {
	Buffer *underlying_stream;
	uint8_t byte;
	uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename){
	BitWriter *buf = (BitWriter *) malloc(sizeof(BitWriter));
	Buffer *underlying_stream = write_open(filename);
	if (underlying_stream == NULL){
		write_close(&underlying_stream);
		fprintf(stderr, "underlying stream is null");
		exit(1);
	}
	buf->underlying_stream = underlying_stream;
	BitWriter *pbuf = buf;
	if (pbuf != NULL){
		return pbuf;
	}
	else{
		fprintf(stderr, "pbuf is null");
		exit(1);
	}
	return NULL;
}

void bit_write_close(BitWriter **pbuf){
	if ((*pbuf)->bit_position > 0){
		write_uint8((*pbuf)->underlying_stream, (*pbuf)->byte);
		(*pbuf)->byte = 0;
		(*pbuf)->bit_position = 0;
	}
	write_close(&((*pbuf)->underlying_stream));
	if (pbuf != NULL && *pbuf != NULL){
		free(*pbuf);
	}
	if (pbuf != NULL){
		*pbuf = NULL;
	}
}

void bit_write_bit(BitWriter *buf, uint8_t x){
	if (buf->bit_position > 7){
		write_uint8(buf->underlying_stream, buf->byte);
		buf->byte = 0x00;
		buf->bit_position = 0;
	}
	if (x & 1){
		buf->byte |= (x & 1) << buf->bit_position;
	}
	buf->bit_position++;
}

void bit_write_uint8(BitWriter *buf, uint8_t x){
	uint8_t bit;
	for (uint8_t i = 0; i <= 7; i++){
		bit = x & 1;
		bit_write_bit(buf, bit);
		x >>= 1;
	}
}

void bit_write_uint16(BitWriter *buf, uint16_t x){
	uint8_t bit;
	for (uint8_t i = 0; i <= 15; i++){
		bit = x & 1;
		bit_write_bit(buf, bit);
		x >>= 1;
	}
}

void bit_write_uint32(BitWriter *buf, uint32_t x){
	uint8_t bit;
	for (uint8_t i = 0; i <= 31; i++){
		bit = x & 1;
		bit_write_bit(buf, bit);
		x >>= 1;
	}
}
