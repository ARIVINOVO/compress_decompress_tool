#include "c_d.h"

int ziptext()
{
    char filename[50];
    printf("输入目标文件名:");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        perror("");
        return -1;
    }
    statistics st[256];
    st_frequency(fp, st);
    int n = 0;
    statistics *weight = getweight(st , &n);

    int all_chars = 0;
    for (int i = 0; i < 256; i++)
        all_chars += st[i].frequency;

    huffnode huff[2*n-1];
    make_huffman(huff, weight, n);
    huffcode huff_code[256];
    make_huffcode(huff, huff_code, n);
    printf("输入输出文件名:");
    scanf("%s", filename);
    FILE *fp1 = fopen(filename,"wb");
    if (fp1 == NULL)
    {
        perror("");
        return -1;
    }

    fwrite(&all_chars, sizeof(int), 1, fp1);
    fwrite(&n, sizeof(int), 1, fp1);
    for (int i = 0; i < n; i++) {
        fwrite(&weight[i].ch, sizeof(unsigned char), 1, fp1);
        fwrite(&weight[i].frequency, sizeof(int), 1, fp1);
    }

    rewind(fp);
    BitWriter bw;
    init_bit_writer(&bw, fp1);
    int c;
    while ((c = fgetc(fp)) != EOF) {
        for (int i = 0; i < n; i++) {
            if (c == huff_code[i].ch) {
                char *code = huff_code[i].cd + huff_code[i].start;
                for (int j = 0; code[j]; j++) {
                    write_bit(&bw, code[j] == '1' ? 1 : 0);
                }
                break;
            }
        }
    }
    flush_bits(&bw);
    fclose(fp);
    fclose(fp1);
    free(weight);
    return 0;
}