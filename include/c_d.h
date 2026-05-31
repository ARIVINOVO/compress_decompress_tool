#ifndef _C_D_H_
#define _C_D_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 1000

typedef struct 
{
    unsigned char ch;
    int frequency;
}statistics;

typedef struct huffnode
{
    int data;
    int freq;
    int parent;
    int left, right;
}huffnode;

typedef struct 
{
    char cd[N];
    int start;
    char ch;
}huffcode;

// 位写入器结构
typedef struct {
    FILE *fp;
    unsigned char buffer;   // 当前累积的字节
    int bit_count;          // buffer 中已写入的位数（0～7）
} BitWriter;

typedef struct 
{
    FILE *fp;
    unsigned char buffer;
    int count;
}BitReader;


void st_frequency(FILE *, statistics *);
statistics* getweight(statistics *, int *);                     //统计频率表

void make_huffman(huffnode *,statistics *, int );            //构建哈夫曼树

void make_huffcode(huffnode *, huffcode *, int);             //哈夫曼编码

void init_bit_writer(BitWriter *bw, FILE *fp);
void write_bit(BitWriter *bw, int bit);
void flush_bits(BitWriter *bw);

void init_bit_reader(BitReader *br, FILE *fp);
int read_bit(BitReader *br);

int ziptext(void);                                        //压缩文件

int unziptext(void);                                        //解压文件

#endif