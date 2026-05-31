#include "c_d.h"

void init_bit_reader(BitReader *br, FILE *fp) {
    br->fp = fp;
    br->buffer = 0;
    br->count = 0;
}

int read_bit(BitReader *br) {
    if (br->count == 0) 
    {
        if (fread(&br->buffer, 1, 1, br->fp) != 1) 
            return EOF;
        br->count = 8;
    }
    int bit = (br->buffer >> 7) & 1;
    br->buffer = br->buffer << 1;
    br->count--;
    return bit;
}