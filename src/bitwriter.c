#include "c_d.h"

void init_bit_writer(BitWriter *bw, FILE *fp) {
    bw->fp = fp;
    bw->buffer = 0;
    bw->bit_count = 0;
}

void write_bit(BitWriter *bw, int bit) {
    bw->buffer |= (bit << (7 - bw->bit_count));
    bw->bit_count++;
    if (bw->bit_count == 8) {
        fwrite(&bw->buffer, 1, 1, bw->fp);
        bw->buffer = 0;
        bw->bit_count = 0;
    }
}

void flush_bits(BitWriter *bw) {
    if (bw->bit_count > 0) {
        fwrite(&bw->buffer, 1, 1, bw->fp);
        bw->buffer = 0;
        bw->bit_count = 0;
    }
}